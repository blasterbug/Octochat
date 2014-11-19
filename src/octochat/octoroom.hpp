#ifndef OCTOROOM_HPP
#define OCTOROOM_HPP

/**
 * @file octoroom.hpp
 *
 * @section desc File description
 *
 * header for room class
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


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <boost/serialization/map.hpp>
#include <boost/assign/list_inserter.hpp>
#include "octouser.hpp"
#include "octomail.hpp"

#define MESSAGE_STACK_SIZE 50

class octomail;

/**
 * Exceptions throwed by octoroom class
 */
class octoroom_exception : std::exception {
	private:
		std::string __cause; /** store exception description */
	public:
		/** constructor
		 * @param[in] cause description of exception origin
		 */
		octoroom_exception( std::string cause ) :
			__cause( cause )
			{};

		/** destructor
		 * currently, do anything special
		 */
		virtual ~octoroom_exception() throw() {
			// do nothing
		};

		/** virtual fonction from superclass,
		 * usefull to get the exception description
		 */
		virtual const char* what()const throw() {
			return __cause.c_str();
		};
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
		std::vector< const octomail* > __messages; /// Messages in da room
		int __msg_idx; /// current index of the last message posted in the room


	public:

		/**
		 * Contructor for octo-room
		 * @param[in] owner The octo-user who created the room
		 * @param[in] title The subject of the room
		 */
		octoroom( octouser* owner, std::string title ) :
			__creator( owner ),
			__subject( title ),
			__userlist(),
			__bannedusers()
		{
			__msg_idx = 0;
			__messages = std::vector< const octomail* >( MESSAGE_STACK_SIZE );
			// add the owner in his own room
			__userlist[ owner->get_name() ] = owner;
		};

		/**
		 * Adding user in the room
		 * @param[in] user User to add in the room
		 * @exception Octoroom_exception throwed if the user is already registered
		 */
		void add_user( octouser *user ) {
			const std::string user_name = user->get_name();
			if ( 1 > __bannedusers.count( user_name ) ) {
				__userlist[ user_name ] = user;
			} else {
				throw octoroom_exception( "Octo-user already in the room" );
			}
		};

		/*void ban_user( octouser &user ) const {
			const string user_name = user->get_name();
			if(__userlist.count( user_name ))
				__userlist.erase( user_name );
			__bannedusers[ user_name ] = user;
		};*/

		void post( const octomail *mail ) {
			/// \todo muted user ? banned user ? etc.
			__messages[ __msg_idx++ ] = mail;
			__msg_idx %= MESSAGE_STACK_SIZE; // stay in the vector boundaries
			std::cout << __msg_idx << std::endl;
		};

};

#endif
