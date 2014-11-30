#ifndef OCTOSTATE_HPP
#define OCTOSTATE_HPP

/**
 * @file octostate.hpp
 *
 * @section desc File description
 *
 * Header file for octosession abstract state (design pattern from GoF)
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

/**
 * Class to represent a state
 */
class octostate
{
	public:
		/// connection transition
		void connect();
		/// deconnection transition
		void disconnect();
		/// start the session
		void start_session();
		/// stop the session
		void close_session();
		/// Set the nickname for the user
		void set_nickname( std::string );
		/// receive a new mail
		void receive_mail( octomail mail );
		/// send a new octomail
		void send_mail( octomail mail );
};

#endif
