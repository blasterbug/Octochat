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
		// octostate implementation
		/**
		 * connection transition
		 */
		virtual void connect() {}
		/**
		 * deconnection transition
		 */
		virtual void disconnect() {}
		/**
		 * start the session
		 */
		virtual void start_session() {}
		/**
		 * stop the session
		 */
		virtual void close_session() {}
		/**
		 * receive a new mail
		 * @param[in] mail mail to post in local(s) octoroom
		 */
		virtual void receive_mail( octomail mail ) {}
		/**
		 * post a new octomail
		 * @param[in] mail The octomail to send to peers octorooms
		 */
		virtual void send_mail( octomail mail ) {}
		/**
		 * change the nickname of the octo-user
		 * @param[in] nickname The octo-ouser name
		 */
		virtual void set_nickname( std::string& nickname ) {}
};

/**
 * List of all states possible
 * Usefull for notify octosession observers when its state changes
 */
enum octostates_name {
	connected = 0,
	deconnected,
	waiting
};

#endif
