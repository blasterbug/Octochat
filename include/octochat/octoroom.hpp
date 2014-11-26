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
#include "octochat/octouser.hpp"
#include "octochat/octomail.hpp"

/// Amount of messages to store
#define MESSAGE_STACK_SIZE 5

/**
 * Exceptions throwed by octoroom class
 */
class octoroom_exception : public std::exception
{
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
		virtual ~octoroom_exception() throw()
		{
			// do nothing
		}

		/** virtual fonction from superclass,
		 * usefull to get the exception description
		 */
		virtual const char* what()const throw()
		{
			return __cause.c_str();
		}
};

/**
 * An octo-room is the place where octo-users chat
 */
class octoroom
{

	private:
		octouser* __creator; /// Who created the room ? -Can be a ghost
		std::string __subject; /// subject of the room
		std::map < const std::string, octouser* > __userlist; /// octo-users in the room
		// currently non implmented
		std::map < const std::string, octouser* > __bannedusers; /// Who is not allowed here
		std::vector< octomail* > __messages; /// Messages in da room
		int __last_msg; /// current index of the last message posted in the room
		int __first_msg; /// index of the first message posted in the room

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
			__bannedusers(),
			__messages( std::vector< octomail* >( MESSAGE_STACK_SIZE ) ),
			__last_msg( 0 ),
			__first_msg( 0 )
		{}

		/**
		 * Who is the owner of the room ?
		 * @param[out] Name of the owner
		 */
		std::string get_owner_name(){
			return __creator->get_name();
		}
		/**
		 * Adding user in the room
		 * @param[in] user User to add in the room
		 * @exception Octoroom_exception throwed if the user is already registered
		 */
		void add_user( octouser* user )
		{
			const std::string user_name = user->get_name();
			if ( 1 > __bannedusers.count( user_name ) )
			{
				__userlist[ user_name ] = user;
			}
			else
			{
				throw octoroom_exception( user_name + " already joined " + __subject );
			}
		}

		/**
		void ban_user( octouser &user ) const
		{
			const string user_name = user->get_name();
			if(__userlist.count( user_name ))
				__userlist.erase( user_name );
		}
		*/

		/**
		 * Post a new octomail into the room
		 * @param[int] mail mail to post
		 */
		void post( octomail mail )
		{
			/// \todo muted user ? banned user ? etc.
			if ( 0 == __messages[ __last_msg ] )
			{
				delete __messages[ __last_msg ];
			}
			__messages[ __last_msg++ ] = new octomail( mail );
			__last_msg %= MESSAGE_STACK_SIZE; // stay in the vector boundaries
			if ( __last_msg == __first_msg )
			{
				__first_msg = ++__first_msg % MESSAGE_STACK_SIZE;
			}
		}

		/**
		 * Get a string representation of the room.
		 * In particular, get the list of the last messages
		 * @param[out] String representation of the room
		 */
		std::string to_string()
		{
			// circular roaming into the messages vector
			int read_idx = __first_msg;
			std::string ret = "";
			while(__last_msg != read_idx)
			{
				if( __messages[ read_idx ] )
				{
					ret += __messages[ read_idx++ ]->to_string() + "\n";
				}
				read_idx %= MESSAGE_STACK_SIZE;
			}
			return ret;
		}

		/**
		 * test if a name is already use
		 * @param[in] name to test
		 * @param[out] true if the name is used, else false
		 */
		bool name_is_used( std::string name )
		{
			return 1 <= __userlist.count( name );
		}

		/**
		 * Get the title of a room
		 * @param[out] The octoroom subject
		 */
		std::string get_subject( )
		{
			return __subject;
		}
		
		/**
		 * change the title of a room
		 * @param[in] new_subject The new topoc of the octoroom
		 */
		void set_subject( std::string new_subject )
		{
			__subject = new_subject;
		}
};

#endif
