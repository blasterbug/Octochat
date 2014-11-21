/**
 * @file octoroom.cpp
 *
 * @section desc File description
 *
 * implementation file for octoroom
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

/**
 * Contructor for octo-room
 * @param[in] owner The octo-user who created the room
 * @param[in] title The subject of the room
 */
octoroom::octoroom( octouser* owner, std::string title ) :
	__creator( owner ),
	__subject( title ),
	__userlist(),
	__bannedusers()
{
	__msg_idx = 0;
	__messages = std::vector< octomail* >( MESSAGE_STACK_SIZE );
	// add the owner in his own room
	__userlist[ owner->get_name() ] = owner;
}

/**
 * Adding user in the room
 * @param[in] user User to add in the room
 * @exception Octoroom_exception throwed if the user is already registered
 */
void octoroom::add_user( octouser* user ) {
	const std::string user_name = user->get_name();
	if ( 1 > __bannedusers.count( user_name ) )
		__userlist[ user_name ] = user;
	else
		throw octoroom_exception( "Octo-user already in the room" );
}

/*void ban_user( octouser &user ) const {
	const string user_name = user->get_name();
	if(__userlist.count( user_name ))
		__userlist.erase( user_name );
}*/

#include <iostream>

/**
 * Post a new octomail into the room
 * @param[int] mail mail to post
 */
void octoroom::post( octomail mail ) {
	/// \todo muted user ? banned user ? etc.
	if ( 0 == __messages[ __msg_idx ] )
		delete __messages[ __msg_idx ];
	__messages[ __msg_idx++ ] = new octomail( mail );
	__msg_idx %= MESSAGE_STACK_SIZE; // stay in the vector boundaries
}

/**
 * Get a string representation of the room.
 * In particular, get the list of the last messages
 * @param[out] String representation of the room
 * \todo fix it
 */
std::string octoroom::to_string() {
	// circular roam into the messages vector

	int last_idx = (0 - 1) % MESSAGE_STACK_SIZE;
	int read_idx = (MESSAGE_STACK_SIZE + last_idx) % MESSAGE_STACK_SIZE;
	std::cout << last_idx << std::endl;
	std::string ret = "";
	//while(last_idx != read_idx){
		ret += __messages[ read_idx ]->to_string() + "\n";
		read_idx = --read_idx % MESSAGE_STACK_SIZE;
	//}
	return ret;
}
