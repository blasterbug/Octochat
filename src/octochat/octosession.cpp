/**
 * @file octosession.cpp
 *
 * @section desc File description
 *
 * Define a session in the octosystem, use state design pattern by GoF
 *
 * @section copyright Copyright
 *
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; version 2
 * of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * @section infos File informations
 *
 * @date 2014/11/10
 * @author Benjamin Sientzoff
 * @version 0.2
 */

#include <string>
#include "octochat/octosession.hpp"
#include "octochat/octostates.hpp"
#include "octochat/octoquery_handler.hpp"

/**
 * constructor
 * @param[in] server Octonet instance
 */
octosession::octosession( octonet* server ) :
	// initiate states
	__deco_state( deconnected_octostate( this ) ),
	__wait_state( waiting_octostate( this ) ),
	__connected_state( connected_octostate( this ) ),
	__current_state( &__deco_state ),
	// initiate session stuffs
	__local_manager(),
	__postman( new octopostman( server ) )
{
	// register an observer to get notified on new queries
	server->add_query_observer( new octoquery_handler( __local_manager ) );
}

/**
 *  getter for state pattern : deconnected state
 * @param[out] deconnected state
 */
octostate octosession::get_deconnected_state()
{
	return __deco_state;
}
/**
 * getter for state pattern : connected state
 * @param[out] connected state
 */
octostate octosession::get_connected_state()
{
	return __connected_state;
}
/**
 * getter for state pattern : waiting state
 * @param[out] waiting state
 */
octostate octosession::get_waiting_state()
{
	return __wait_state;
}
/**
 * setter for state pattern
 * @param[in] state The nex state
 * This function is supposed to be only called by octostate objects
 */
void octosession::set_current_state( octostate state )
{
	__current_state = &state;
}
/**
 * When the session is connected
 */
void octosession::connect()
{
	__current_state->connect();
}
/**
 * When the session is being disconnected
 */
void octosession::disconnect(){
	__current_state->disconnect();
}
/**
 *  get the current manager for the session
 * @param[out] reference to octomanager for the session
 */
octomanager* octosession::get_octomanager()
{
	return __local_manager;
}
/**
 * Get the current postman for the current session
 * @param[out] reference to the octopostman for the session
 */
octopostman* octosession::get_octopostman()
{
	return __postman;
}
/**
 *  When receiving octomails from octonetwork
 * @param[in] mail The octomail to post in the local room
 */
void octosession::receive_mail( octomail mail )
{
	__current_state->receive_mail( mail );
}
/**
 * send a mail over the octonetwork
 * @param[in] mail octomail to send
 */
void octosession::send_mail( octomail mail )
{
	__current_state->send_mail( mail );
}
/**
 * start the chat session
 */
void octosession::start_session()
{
	__current_state->start_session();
}
/**
 * close the current session
 */
void octosession::close_session()
{
	__current_state->close_session();
}
/**
 * set the nickname user for the session
 * @param[in] nickname username for the session
 */
void octosession::set_nickname( std::string nickname )
{
	__current_state->set_nickname( nickname );
}
/**
 * get the nickname for the session
 * @return The actual nickname
 */
std::string octosession::get_nickname()
{
	return __username;
}
/**
 * Change the name of the user
 * (only callable from octostates )
 * @param[in] nickname The new nickname
 */
void octosession::edit_nickname( std::string nickname )
{
	__username = nickname;
}
