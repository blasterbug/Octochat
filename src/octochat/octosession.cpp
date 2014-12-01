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
	// At programm start up, the session is deconnected
	__current_state( new deconnected_octostate( this ) ),
	// initiate session stuffs
	__local_manager(),
	__postman( new octopostman( server ) )
{
	// register an observer to get notified on new queries
	server->add_query_observer( new octoquery_handler( __local_manager, this ) );
}
/**
 * setter for state pattern
 * @param[in] state The nex state
 * This function is supposed to be only called by octostate objects
 */
void octosession::set_current_state( octostate* state )
{
	__current_state = state;
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
#include <iostream>
/**
 * start the chat session
 */
void octosession::start_session()
{
	__current_state->start_session();
	std::cout << "conntection with " << __username << std::endl;
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
void octosession::set_nickname( std::string& nickname )
{
	std::cout << "changing username with " << __username << std::endl;
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
	std::cout << "j'edite " << __username << std::endl ;
	std::cout << nickname << std::endl;
	std::cout << __username << std::endl;
}
/**
 * Send a query to an octo-user when he tried to joint
 * the local octo-room
 * @param[in] user user for the connection
 * @param[in] accepted True if the user joined, else false
 */
void octosession::notify_user_auth( octouser* user, bool added )
{
	if ( added )
	{
		__postman->send_auth_ok( user, __username );
	}
	else
	{
		__postman->send_auth_ko( user );
	}
}
