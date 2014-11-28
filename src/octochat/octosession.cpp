/**
 * @file octosession.cpp
 *
 * @section desc File description
 *
 * Define a session in the octosystem, use state design pattern
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
 * @version 0.1
 */

#include <typeinfo.h>
		/// attributs for state pattern
		/// the deconnected state
		const deconnected_octostate __deco_state;
		/// the waiting state
		const waiting_octostate __wait_state;
		/// the connected state
		const connected_octostate __connected_state;

		/// current state of the session
		octostate* __current_state;
		/// room for the session
		octoroom* __room;
		/// user name for the session
		std::string __name;
		/// manage local chat
		octomanager* __local_manager;
		/// manage octonetwork output
		octopostman* __postman;
		
/**
 * constructor
 */
octosession::octosession()
	__deco_state( deconnected_octostate( this ) ),
	__wait_state( waiting_octostate( this ) ),
	__connected_state( connected_octostate( this ) ),
	__current_state( __deco_state ),
	__local_manager( octomanager( this ) ),
	__postman( octopostman( this ) )
{}
/**
 * getter for state pattern : deconnected state
 * @param[out] deconnected state
 */
deconnected_octostate octosession::get_deconnected_state() const
{
	return __deco_state;
}
/** getter for state pattern : connected state
 * @param[out] connected state
 */
connected_octostate octosession::get_connected_state() const
{
	return __connected_state;
}
/** getter for state pattern : waiting state
 * @param[out] waiting state
 */
waiting_octostate octosession::get_waiting_state() const
{
	return __wait_state;
}
/** setter for state pattern
 * @param[in] state The new state of the session
 */
void octosession::set_current_state( const octostate& state ) const
{
	typeid(__current_state) = typeid(state);
}
/**
 * post a new mail into the room
 * @param[in] mail to post into an octoroom
 */
void octosession::receive_mail( octomail mail )
{
	__manager.post( mail );
}
/**
 * send a mail to the octonetwork
 * @param[in] mail  The octomail to send
 */
void octosession::send_mail( octomail mail )
{
	__postman.send( mail )
}
/**
 * Receive an error from the network
 * @param[in] error Error string from the octonetwork
 */
void octosession::receive_error( std::string );
/**
 * Send an error over the octonetwork
 * @param[in] message The error to send
 */
void octosession::send_error( std::strig mesage )
{
	octopeer peer( *user->get_peer() );
	octoquery query;
	query.headers_map[ OCTOCHAT_PROTOCOL_ERR ] = ??; /// \todo
	query.content_str = err_message;
	__network->send_query( peer, query ); /// \todo query send ?
}
/**
 * start the chat session
 * @param[in] nickname Nickname for the user
 */
void start_session( std::string nickname)
{
	__current_state->
}
/**
 * Close the current session
 */
void octosession::close_session()
{
	__current_state.disconnect();
}
