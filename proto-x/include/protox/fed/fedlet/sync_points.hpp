/*
    Copyright (c) 2012 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_EXAMPLES_FEDLET_SYNC_POINTS_HPP
#define PROTOX_EXAMPLES_FEDLET_SYNC_POINTS_HPP

/**********************************************************************************************************************/

namespace protox { namespace fed { namespace fedlet {

/**********************************************************************************************************************/

struct READY_TO_POPULATE {
    static const char *str() { static const char *value = "ReadyToPopulate"; return value; }
};

struct READY_TO_RUN {
    static const char *str() { static const char *value = "ReadyToRun"; return value; }
};

struct READY_TO_RESIGN {
    static const char *str() { static const char *value = "ReadyToResign"; return value; }
};

/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
