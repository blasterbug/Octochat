/**
 * @file octostates.cpp
 *
 * @section desc File description
 *
 * The octosession states (design pattern from GoF)
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
 * @date 2014/11/11
 * @author Benjamin Sientzoff
 * @version 0.1
 */

#include "octochat.hpp"
#include "octochat/octostate.hpp"
#include "octochat/octostates.hpp"

// octostate implementation
/**
 * connection transition
 */
void octostate::connect() {}
/**
 * deconnection transition
 */
void octostate::disconnect() {}
/**
 * start the session
 */
void octostate::start_session() {}
/**
 * stop the session
 */
void octostate::close_session() {}
/**
 * receive a new mail
 * @param[in] mail mail to post in local(s) octoroom
 */
void octostate::receive_mail( octomail mail ) {}
/**
 * post a new octomail
 * @param[in] mail The octomail to send to peers octorooms
 */
void octostate::send_mail( octomail mail ) {}
/**
 * change the nickname of the octo-user
 * @param[in] nickname The octo-ouser name
 */
void octostate::set_nickname( const std::string &nickname ) {}

 // connected_octostate implementation
/**
 * constructor
 * @param[in] session The current session
 */
connected_octostate::connected_octostate( octosession* session ) :
	__session( session )
{}
void connected_octostate::receive_mail( octomail mail )
{
	__session->get_octomanager()->post( mail );
}
void connected_octostate::send_mail( octomail mail )
{
	__session->get_octopostman()->send( mail );
}
void connected_octostate::close_session()
{
	__session->set_current_state( __session->get_waiting_state() );
	__session->notify( deconnected );
	//__session->get_octopostman()->byebye();
	/// \todo send a query to locals peers when users is being deconnected
}

// deconnected_octostate implementation
deconnected_octostate::deconnected_octostate( octosession* session ) :
	__session( session )
{}
/// start the session (i.e try to connect to peers octorooms )
void deconnected_octostate::start_session() {
	// the session is now waiting for be connected to peers octorooms
	__session->set_current_state( __session->get_waiting_state() );
	// send query to connect
	__session->get_octopostman()->register_user(
							__session->get_nickname(), OCTOCHAT_DEFAULT_ROOM_NAME );
	__session->notify( waiting );
}
#include <iostream>
/// change the nickname for chat
void deconnected_octostate::set_nickname( const std::string& nickname )
{
	// change name of the user
	// call set_nickname cause calling this function => infinite loop
	__session->edit_nickname( nickname );
	std::cout << nickname << " edit" << std::endl;
}

// waiting_octostate implementation
	/**
 * constructor
 * @param[in] session The current session
 */
waiting_octostate::waiting_octostate( octosession* session ) :
	__session( session )
{}
/// function to pass from waiting state to deconnected state
void waiting_octostate::disconnect()
{
	__session->set_current_state( __session->get_deconnected_state() );
	__session->notify( deconnected );
}
/// function to pass from waiting state to connected state
void waiting_octostate::connect()
{
	__session->set_current_state( __session->get_connected_state() );
	__session->notify( connected );
}
