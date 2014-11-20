 #ifndef OCTOROOM_HPP
 #define OCTOROOM_HPP

/**
 * @file octoroom.cpp
 *
 * @section desc File description
 *
 * header for octoroom class
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
 * @date 2014/10/16
 * @author Benjamin Sientzoff
 * @version 0.1
 */

class octoroom;

#include <string>
#include <vector>
#include <map>
#include "octouser.hpp"
#include "octomail.hpp"

/// Amount of messages to store
#define MESSAGE_STACK_SIZE 50

/**
 * Exceptions throwed by octoroom class
 */
class octoroom_exception : public std::exception {
	private:
		std::string __cause; /** store exception description */
	public:
		/** constructor
		 * @param[in] cause description of exception origin
		 */
		octoroom_exception( std::string cause ) :
			__cause( cause )
			{}

		/** destructor
		 * currently, do anything special
		 */
		virtual ~octoroom_exception() throw() {
			// do nothing
		}

		/** virtual fonction from superclass,
		 * usefull to get the exception description
		 */
		virtual const char* what()const throw() {
			return __cause.c_str();
		}
};

/**
 * An octo-room is the place where octo-users chat
 */
class octoroom {

	private:
		octouser* __creator; /// Who created the room ? -Can be a ghost
		std::string __subject; /// subject of the room
		std::map < const std::string, octouser* > __userlist; /// Who is in the room?
		std::map < const std::string, octouser* > __bannedusers; /// Who is not allowed here
		std::vector< octomail* > __messages; /// Messages in da room
		int __msg_idx; /// current index of the last message posted in the room

	public:
		/// constructor for octoroom
		octoroom( octouser*, std::string );
		/// add an octo-user in the room
		void add_user( octouser* );
		/// \todo ban user from the room
		/*void ban_user( octouser &user ) const;*/
		/// post an message into the room
		void post( octomail );
		/// get a string representation of the room
		std::string to_string();
};

#include "octoroom.cpp"

#endif
