#ifndef OCTOCHAT_HPP
#define OCTOCHAT_HPP

/**
 * @file octouser.hpp
 *
 * @section desc File description
 *
 * header for octouser class
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
 * @date 2014/10/07
 * @author Benjamin Sientzoff
 * @version 0.2
 */


#include <string>
#include <vector>
#include <map>

#include "octonet/octopeer.hpp"

/// Amount of messages to store
#define OCTOROOM_MESSAGE_STACK_SIZE 5

/// define a default name for octorooms
#define OCTOCHAT_DEFAULT_ROOM_NAME "octochat hub"

class octouser {

	private:
		std::string __name; /// user (unique) name
		const octopeer* __peer; /// "connect" to user
		bool __alive; /// Is the user on/offline ?

	public:

		/**
		 * Create a new user
		 * @param[in] name (Nick)name of the user
		 * @param[in] peer object for an user
		 */
		octouser( std::string name, const octopeer* peer) :
			__name( name ),
			__peer( peer ),
			__alive( true )
		{}

		/**
		 * Copy contructor, make a copy of the object
		 * @param[in] tocopy Octo-user to copy
		 */
		octouser( const octouser& tocopy ) :
			__name( tocopy.__name ),
			__peer( tocopy.__peer ),
			__alive( tocopy.__alive )
		{}

		/**
		 * What is the name of the user ?
		 * @param[out] Name of the user
		 */
		std::string get_name() const
		{
			return __name;
		}

		/**
		 * Get the octopeer from the user
		 * @param[out] Octopeer pointer to the octopeer for the user
		 */
		const octopeer* get_peer()
		{
			return __peer;
		}

		/**
		 * Is the user online ?
		 * @param[out] True if the user is online, else false is returned
		 */
		bool is_online() const
		{
			return __alive;
		}
};

/**
 * Octomail is a message send by an octouser into an octoroom
 */
class octomail
{

	private:
		std::string __from; /// Whoe send the message?
		const std::string __destination; /// Where the message should be posted?
		std::string __content; /// Content of the message, i.e. text bitch!
		int __timeStmp; /// When the message was created? (local time) \todo

	public:
		/**
		 * constructor for a octo-mail
		 * @param[in] writer the emitter of the message
		 * @param[in] adressee Where the mail should be posted ?
		 * @param[in] text content of the message
		 */
		octomail( std::string writer, std::string adressee, std::string text ) :
			__from( writer ),
			__destination( adressee ),
			__content( text ),
			__timeStmp( 0 ) /// TODO
		{}

		/**
		 * copy contructor for octo-mail
		 * @param[in] tocopy octo-mail to be copied
		 */
		octomail( const octomail& tocopy ) :
			__from ( tocopy.__from ),
			__destination( tocopy.__destination ),
			__content( tocopy.__content ),
			__timeStmp( tocopy.__timeStmp )
		{}

		/**
		 * get the string representation of an octouser
		 * @param[out] name of the octo-user
		 */
		const std::string get_writer_name() const
		{
			return __from;
		}

		/**
		 * Get the content of an octomail
		 * @param[out] content of the mail
		 */
		const std::string get_content() const
		{
			return __content;
		}

		/**
		 * get the string representation of the octomail
		 * @param[out] The octomail as a string
		 */
		const std::string to_string() const
		{
			return __from + " : " + __content;
		}

		/**
		 * get the name of the mail destination
		 * @param[out] destination of the mail
		 */
		const std::string get_destinee() const
		{
			return __destination;
		}
};


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
	std::string __roomname; /// The name of the octoroom
		octouser* __creator; /// Who created the room ?
		std::string __subject; /// subject of the room, for the moment useless
		std::map < const std::string, octouser* > __user_list; /// octo-users in the room
		// currently non implmented
		std::map < const std::string, octouser* > __banned_users; /// Who is not allowed here
		std::vector< octomail* > __messages; /// Messages in da room
		int __last_msg; /// current index of the last message posted in the room
		int __first_msg; /// index of the first message posted in the room

	public:
		/**
		 * Contructor for octo-room
		 * @param[in] owner The octo-user who created the room
		 * @param[in] name The name of the room
		 */
		octoroom( octouser* owner, std::string name ) :
			__creator( owner ),
			__roomname( name ),
			__user_list(),
			__banned_users(),
			__messages( std::vector< octomail* >( OCTOROOM_MESSAGE_STACK_SIZE ) ),
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
			if ( 1 > __banned_users.count( user_name ) )
			{
				__user_list[ user_name ] = user;
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
			__last_msg %= OCTOROOM_MESSAGE_STACK_SIZE; // stay in the vector boundaries
			// if erasing first posted messages
			if ( __last_msg == __first_msg )
			{
				// increment the pointer to it
				__first_msg = ++__first_msg % OCTOROOM_MESSAGE_STACK_SIZE;
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
				read_idx %= OCTOROOM_MESSAGE_STACK_SIZE;
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
			return 1 <= __user_list.count( name );
		}

		/**
		 * Get the name of the octoroom
		 * @param[out] The name of the octoroom
		 */
		std::string get_name()
		{
			return __roomname;
		}

		/** currently incompleted implementation, we're working on
		 * Get the title of a room
		 * @param[out] The octoroom subject
		 *
		std::string get_subject()
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
