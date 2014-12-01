#ifndef OCTOSTATES_HPP
#define OCTOSTATES_HPP

/**
 * @file octostates.hpp
 *
 * @section desc File description
 *
 * Header file for octosession states (design pattern from GoF)
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

#include "octochat.hpp"
#include "octochat/octostate.hpp"
#include "octochat/octosession.hpp"

/**
 * connected state class
 */
class connected_octostate : public octostate
{
	protected:
		/// the current session with the state
		octosession* __session;
	public:
		/// constructor
		connected_octostate( octosession* );
		/// receive an octomail
		void receive_mail( octomail );
		/// Send an octomail
		void send_mail( octomail );
		/// close the running session
		void close_session();
};

/// deconnected state class
class deconnected_octostate : public octostate
{
	protected:
		/// the current session with the state
		octosession* __session;
	public:
		/// constructor
		deconnected_octostate( octosession* );
		/// start the session (i.e try to connect to peers octorooms )
		void start_session();
		/// change the nickname for chat
		void set_nickname( std::string& );
};

/// waiting state
class waiting_octostate : public octostate
{
	protected:
		/// the current session with the state
		octosession* __session;
	public:
		/// constructor
		waiting_octostate( octosession* session );
		/// function to pass from waiting state to deconnected state
		void disconnect();
		/// function to pass from waiting state to connected state
		void connect();
};

#endif
