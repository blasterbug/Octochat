#ifndef OCTOSESSION_HPP
#define OCTOSESSION_HPP

/**
 * @file octosession.cpp
 *
 * @section desc File description
 *
 * Header file to Define a session in the octosystem, use state design pattern
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

#include <string>

#include "octonet/octonet.hpp"

#include "octochat/octouser.hpp"
#include "octochat/octomail.hpp"
#include "octochat/octoroom.hpp"

#include "octochat/octostate/octostates.hpp"

/**
 * Class to represent a session
 */
class octosession
{
	private:
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
		/// user for the session
		octouser* __user;
		/// manage local chat
		octomanager* __local_manager;
		/// manage octonetwork output
		octopostman* __postman;

	public:
	/// constructor
	octosession();
	/// getter for state pattern : deconnected state
	deconnected_octostate get_deconnected_state() const;
	/// getter for state pattern : connected state
	connected_octostate get_connected_state() const ;
	/// getter for state pattern : waiting state
	waiting_octostate get_waiting_state() const;
	/// setter for state pattern
	void set_current_state( const octostate& state ) const;
	/// get the current manager for the session
	octomanager* get_octosmanager();
	/// Get the current postman for the current session
	octopostman* get_octopostman();
	/// post a new mail into a room
	void receive_mail( octomail );
	/// send a mail to the octonetwork
	void send_mail( octomail );
	/// Receive an error from the network
	void receive_error( std::string );
	/// Send a error over the octonetwork
	void send_error( std::strig );
	/// start the chat session
	void start_session( std::string );
	/// close the current session
	void close_session();

}
#endif
