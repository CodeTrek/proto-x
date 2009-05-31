/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_ALGORITHM_STRING_TOKENIZE_HPP
#define PROTOX_ALGORITHM_STRING_TOKENIZE_HPP

/******************************************************************************/

#include <string>
#include <sstream>
#include <vector>

/******************************************************************************/

namespace protox { namespace algorithm { namespace string {

/******************************************************************************/

void tokenize( const std::string &str,
               char delim,
               std::vector< std::string > &result )
{
  std::istringstream iss( str );
  std::string token;
  while( getline( iss, token, delim ) )
  {
    result.push_back( token );
  }
}

/**************************************************************************************************/

}}} // protox::algorithm::string

/**************************************************************************************************/

#endif

/**************************************************************************************************/
