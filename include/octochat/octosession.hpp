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

#include "octochat.hpp"
#include "octochat/octomanager.hpp"
#include "octochat/octopostman.hpp"
#include "octochat/octostate.hpp"
#include "octochat/octo_subject.hpp"
/**
 * Class to represent a session
 */
class octosession : public octo_subject
{
	private:
		/// attributs for state pattern
		/// the deconnected state
		octostate __deco_state;
		/// the waiting state
		octostate __wait_state;
		/// the connected state
		octostate __connected_state;

		/// current state of the session
		octostate* __current_state;
		/// room for the session
		octoroom* __room;
		/// user for the session
		std::string __username;
		/// manage local chat
		octomanager* __local_manager;
		/// manage octonetwork output
		octopostman* __postman;

	public:
	/// constructor
	octosession( octonet* );
	/// getter for state pattern : deconnected state
	octostate get_deconnected_state();
	/// getter for state pattern : connected state
	octostate get_connected_state();
	/// getter for state pattern : waiting state
	octostate get_waiting_state();
	/// setter for state pattern
	void set_current_state( octostate );
	/// When the session is connected
	void connect();
	/// When the session is being disconnected
	void disconnect();

	/// get the current manager for the session
	octomanager* get_octomanager();
	/// Get the current postman for the current session
	octopostman* get_octopostman();
	/// post a new mail into a room
	void receive_mail( octomail );
	/// send a mail to the octonetwork
	void send_mail( octomail );
	/// start the chat session
	void start_session();
	/// close the current session
	void close_session();
	/// set the nickname user for the session
	void set_nickname( std::string );
	/// get the nickname for the session
	std::string get_nickname();
	/// Change the name of the user (only callable from octostates
	void edit_nickname( std::string );
	/// send a query to an octo-user when he tried to joint the local room
	void notify_user_auth( octouser*, bool );

};
#endif
