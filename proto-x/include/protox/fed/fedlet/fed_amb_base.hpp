
/*
    Copyright (c) 2012 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_FED_FEDLET_FED_AMB_BASE_HPP
#define PROTOX_FED_FEDLET_FED_AMB_BASE_HPP

/**********************************************************************************************************************/

#include <iostream>
#include <string>

#include <fedtime.hh>
#include <RTI.hh>
#include <NullFederateAmbassador.hh>

/**********************************************************************************************************************/

namespace protox { namespace fed { namespace fedlet {

/**********************************************************************************************************************/

class fed_amb_base : public NullFederateAmbassador {
    private:
        static double convert_time(const RTI::FedTime &the_time) {
            return ((RTIfedTime) the_time).getTime();
        }

        double fed_time;
        double fed_lookahead_time;

        bool is_regulating;
        bool is_constrained;
        bool is_advancing;

    public:
        fed_amb_base() :
            fed_time(0.0),
            fed_lookahead_time(1.0),
            is_regulating(false),
            is_constrained(false),
            is_advancing(false)
        {}

        virtual ~fed_amb_base() throw (RTI::FederateInternalError) {}
  
        //////////////////////////////////////////////////////////////////////////////
        // Time Callbacks
        //////////////////////////////////////////////////////////////////////////////
        virtual void timeRegulationEnabled(const RTI::FedTime &theFederateTime)
            throw (RTI::InvalidFederationTime,
                   RTI::EnableTimeRegulationWasNotPending,
                   RTI::FederateInternalError) {
            is_regulating = true;
            fed_time = convert_time(theFederateTime);
        }

        virtual void timeConstrainedEnabled(const RTI::FedTime &theFederateTime)
            throw (RTI::InvalidFederationTime,
                   RTI::EnableTimeConstrainedWasNotPending,
                   RTI::FederateInternalError) {
            is_constrained = true;
            fed_time = convert_time(theFederateTime);
        }

        virtual void timeAdvanceGrant(const RTI::FedTime &theTime)
            throw (RTI::InvalidFederationTime,
                   RTI::TimeAdvanceWasNotInProgress,
                   RTI::FederateInternalError) {
            is_advancing = false;
            fed_time = convert_time(theTime);
        }

        inline double get_fed_time() const {
            return fed_time;
        }

        inline double get_fed_lookahead_time() const {
            return fed_lookahead_time;
        }

        inline bool is_time_regulating() const {
            return is_regulating;
        }

        inline bool is_time_constrained() const {
            return is_constrained;
        }

        inline void set_time_advancing(bool advancing) {
            is_advancing = advancing;
        }

        inline bool is_time_advancing() const {
            return is_advancing;
        }
};

/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
