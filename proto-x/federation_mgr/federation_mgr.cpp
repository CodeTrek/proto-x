/*
    Copyright (c) 2012 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#include <iostream>
#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/mpl/vector.hpp>

#include <fedtime.hh>
#include <RTI.hh>

#include <protox/hla/o_class_type.hpp>
#include <protox/hla/object_amb.hpp>

#include <protox/fed/fedlet/fed_amb.hpp>
#include <protox/fed/fedlet/sync_points.hpp>

#include <protox/fed/mgr/object_model/som.hpp>

/**********************************************************************************************************************/

using namespace boost;
using namespace protox::hla;
using namespace protox::fed;
using namespace protox::fed::mgr::object_model;

/**********************************************************************************************************************/

typedef o_class_type< federation_mgr_som, q_name< HLAmanager, HLAfederate > >::type federate_type;

/**********************************************************************************************************************/

typedef hla::object_amb< mpl::vector< federate_type > >::type obj_amb_type;

/**********************************************************************************************************************/

class federation_mgr_fed_amb : public fedlet::fed_amb {
    private:
        obj_amb_type &obj_amb;

    public:
        federation_mgr_fed_amb(obj_amb_type &obj_amb) : obj_amb(obj_amb) {}
        ~federation_mgr_fed_amb() throw (RTI::FederateInternalError) {}

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Object Management Services
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        virtual void discoverObjectInstance(RTI::ObjectHandle      theObject,
                                            RTI::ObjectClassHandle theObjectClass,
                                            const char             *theObjectName)
            throw (RTI::CouldNotDiscover,
                   RTI::ObjectClassNotKnown,
                   RTI::FederateInternalError) {
            obj_amb.discover_object(theObjectClass, theObject, theObjectName);
            std::cout << "Federate " << theObjectName << " joined" << std::endl;
        }

        virtual void reflectAttributeValues(RTI::ObjectHandle                       theObject,
                                            const RTI::AttributeHandleValuePairSet &theAttributes,
                                            const RTI::FedTime                     &theTime,
                                            const char                             *theTag,
                                            RTI::EventRetractionHandle              theHandle)
            throw (RTI::ObjectNotKnown,
                   RTI::AttributeNotKnown,
                   RTI::FederateOwnsAttributes,
                   RTI::InvalidFederationTime,
                   RTI::FederateInternalError) {
            obj_amb.reflect_object(theObject, theAttributes, &theTime, theTag);
        }

        virtual void reflectAttributeValues(RTI::ObjectHandle                       theObject,
                                            const RTI::AttributeHandleValuePairSet &theAttributes,
                                            const char                              *theTag)
            throw(RTI::ObjectNotKnown,
                  RTI::AttributeNotKnown,
                  RTI::FederateOwnsAttributes,
                  RTI::FederateInternalError) {
            obj_amb.reflect_object(theObject, theAttributes, 0, theTag);
        }

        virtual void removeObjectInstance(RTI::ObjectHandle           theObject,
                                          const RTI::FedTime         &theTime,
                                          const char                 *theTag,
                                          RTI::EventRetractionHandle  theHandle)
            throw(RTI::ObjectNotKnown,
                  RTI::InvalidFederationTime,
                  RTI::FederateInternalError) {
            obj_amb.remove_object(theObject);
            std::cout << "Federate removed" << std::endl;
        }

        virtual void removeObjectInstance(RTI::ObjectHandle theObject, const char *theTag)
            throw(RTI::ObjectNotKnown,
                  RTI::FederateInternalError) {
            obj_amb.remove_object( theObject );
            std::cout << "Federate removed" << std::endl;
        }
};

static void register_sync_points(RTI::RTIambassador &rti_amb) {
    rti_amb.registerFederationSynchronizationPoint(fedlet::READY_TO_POPULATE::str(), "");
    rti_amb.registerFederationSynchronizationPoint(fedlet::READY_TO_RUN::str(),      "");
    rti_amb.registerFederationSynchronizationPoint(fedlet::READY_TO_RESIGN::str(),   "");
}

static void advance_time(double timestep, RTI::RTIambassador &rti_amb, fedlet::fed_amb_base &fed_amb) {
    fed_amb.set_time_advancing(true);
    const RTIfedTime new_time = (fed_amb.get_fed_time() + timestep);
    rti_amb.timeAdvanceRequest(new_time);

    // wait for the time advance to be granted.
    while (fed_amb.is_time_advancing()) {
        rti_amb.tick();
    }
}

static void enable_time_policy(RTI::RTIambassador &rti_amb, const fedlet::fed_amb_base &fed_amb) {
    const RTIfedTime fed_time = fed_amb.get_fed_time();
    const RTIfedTime lookahead = fed_amb.get_fed_lookahead_time();

    rti_amb.enableTimeRegulation(fed_time, lookahead);

    while (fed_amb.is_time_regulating() == false) {
        rti_amb.tick();
    }

    rti_amb.enableTimeConstrained();

    while (fed_amb.is_time_constrained() == false) {
        rti_amb.tick();
    }
}

static void create_federation_execution(RTI::RTIambassador &rti_amb, const char *name, const char *fed_file) {
    try {
        rti_amb.createFederationExecution(name, fed_file);
        std::cout << "Federation created." << std::endl;
    }
    catch (RTI::FederationExecutionAlreadyExists) {
        std::cout << "Federation already exists." << std::endl;
    }
    catch (RTI::Exception &ex) {
        std::cout <<  ex._name << " " << ex._reason << std::endl;
    }
}

static void destroy_federation_execution(RTI::RTIambassador &rti_amb, const char *name) {
    try {
        rti_amb.destroyFederationExecution(name);
        std::cout << "Federation destroyed." << std::endl;
    }
    catch (RTI::FederationExecutionDoesNotExist) {
        std::cout << "Federtion does not exist." << std::endl;
    }
    catch (RTI::FederatesCurrentlyJoined) {
        std::cout << "Federation not destroyed - other federates are joined." << std::endl;
    }
}

/**
 * A simple manager federate that uses synchronization points and the managment object model (MOM) to coordinate the
 * initialization, execution, and resignation phases of a HLA federation execution.
 *
 * Note: Start this federate before any other federates.
 *
 * Here is a summary of this federates behavior:
 *
 * 1) Create and join a federation execution.
 *
 * 2) Wait for the expected number of federates to join. When the expected number of federates join, register these
 *    synchronization points: "ReadyToPopulate", "ReadyToRun", and "ReadyToResign".
 *
 * 3) Wait for all of the synchronization points to be announced and then signal "ReadyToPopulate" achieved.
 *
 * 4) Wait for "ReadyToPopulate" to be achieved by the other joined federates. When all joined federates achieve
 *    "ReadyToPopulate", signal "ReadyToRun".
 *
 * 5) Wait for "ReadyToRun" to be achieved by the other joined federates. When all joined federates achieve
 *    "ReadyToRun", signal "ReadyToResign".
 *
 * 6) Wait for "ReadyToResign" to be achieved by the other joined federates. When all joined federates achieve
 *    "ReadyToResign", terminate execution.
 */
int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "usage: fed_mgr federation fed_file num_federates\n";
        std::cout << "       federation    - The name of the federation.\n";
        std::cout << "       fed_file      - The federation execution details (FED) file.\n";
        std::cout << "       num_federates - The total number of federates required to join, including"
                                       " this fed_mgr federate.\n";
        std::cout << "\n";
        std::cout << "Example: fed_mgr \"exmaple_federation\" \"./example.fed\" 3\n";

        return -1;
    }

    static const char    *FEDERATION_NAME =       argv[1];
    static const char    *FED_FILE_NAME   =       argv[2];
    static const unsigned NUM_FEDERATES   = atoi(argv[3]);

    using namespace protox::hla;

    RTI::RTIambassador rti_amb;

    create_federation_execution(rti_amb, FEDERATION_NAME, FED_FILE_NAME);

    // Join federation
    obj_amb_type obj_amb;
    federation_mgr_fed_amb fed_amb(obj_amb);
	rti_amb.joinFederationExecution("fed_mgr", FEDERATION_NAME, &fed_amb);
    std::cout << "Federation joined." << std::endl;

    // Initialize handles
    federation_mgr_som::init_handles(rti_amb);
    std::cout << "Handles initialized." << std::endl;

    // subscribe
    federate_type::subscribe(rti_amb);

    // enable time policy
    enable_time_policy(rti_amb, fed_amb);

    bool need_to_register_sync_points = true;
    bool ready_to_populate_achieved   = false;
    bool ready_to_run_achieved        = false;
    bool ready_to_resign_achieved     = false;

    while (true) {
        advance_time(1.0, rti_amb, fed_amb);

        if ((obj_amb.size< federate_type >() >= NUM_FEDERATES) && (need_to_register_sync_points)) {
            try {
                register_sync_points(rti_amb);
                need_to_register_sync_points = false;
            }
            catch (RTI::Exception& ex) {
                std::cout << "RTI Exception: " << ex._name << " " << ex._reason << std::endl;
                break;
            }
        }

        if ((fed_amb.all_sync_points_announced) && (!ready_to_populate_achieved)) {
            try {
                rti_amb.synchronizationPointAchieved(fedlet::READY_TO_POPULATE::str());
                ready_to_populate_achieved = true;
            }
            catch (RTI::Exception& ex) {
                std::cout << "RTI Exception: " << ex._name << " " << ex._reason << std::endl;
                break;
            }
        }

        if ((fed_amb.is_ready_to_populate) && (!ready_to_run_achieved)) {
            try {
                rti_amb.synchronizationPointAchieved(fedlet::READY_TO_RUN::str());
                ready_to_run_achieved = true;
            }
            catch (RTI::Exception& ex) {
                std::cout << "RTI Exception: " << ex._name << " " << ex._reason << std::endl;
                break;
            }
        }

        if ((fed_amb.is_ready_to_run) && (!ready_to_resign_achieved)) {
            try {
                rti_amb.synchronizationPointAchieved(fedlet::READY_TO_RESIGN::str());
                ready_to_resign_achieved = true;
            }
            catch (RTI::Exception& ex) {
                std::cout << "RTI Exception: " << ex._name << " " << ex._reason << std::endl;
                break;
            }
        }

        if (fed_amb.is_ready_to_resign) {
            break;
        }
    }

    return 0;
}

/**********************************************************************************************************************/
