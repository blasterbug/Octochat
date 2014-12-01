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

 //
 // connected_octostate implementation
 //
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
	// enter in the waiting state
	__session->set_current_state( new waiting_octostate( __session ) );
	__session->notify( deconnected );
	/// \todo send a query to locals peers when users is being deconnected
}

 //
 // deconnected_octostate implementation
 //
deconnected_octostate::deconnected_octostate( octosession* session ) :
	__session( session )
{}
/// start the session (i.e try to connect to peers octorooms )
void deconnected_octostate::start_session() {
	// the session is now waiting for be connected to peers octorooms
	__session->set_current_state( new waiting_octostate( __session ) );
	// send query to connect
	__session->get_octopostman()->register_user(
							__session->get_nickname(), OCTOCHAT_DEFAULT_ROOM_NAME );
	__session->notify( waiting );
}
#include <iostream>
/// change the nickname for chat
void deconnected_octostate::set_nickname( std::string& nickname )
{
	std::cout << "(1)" << nickname << " edit" << std::endl;
	std::cout << "(2)" << __session->get_nickname() << " edit" << std::endl;
	// change name of the user
	// call set_nickname cause calling this function => infinite loop
	__session->edit_nickname( nickname );
}

 //
 // waiting_octostate implementation
 //
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
	// the session is now deconnected
	__session->set_current_state( new deconnected_octostate( __session ) );
	__session->notify( deconnected );
}
/// function to pass from waiting state to connected state
void waiting_octostate::connect()
{
	// the session is now connected
	__session->set_current_state( new connected_octostate( __session ) );
	__session->notify( connected );
}
