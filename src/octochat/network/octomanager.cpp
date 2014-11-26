/**
 * @file octomanager.cpp
 *
 * @section desc File description
 *
 * file to manage network query from octonet, implementation
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

#include "octochat/network/octoquery_handler.hpp"
#include "octochat/network/octomanager.hpp"

/**
 * Octomanager contructor
 * @param[in] network Octonet object for communication
 */
octomanager::octomanager( octonet* network ) :
	__network( network )
{
	// register an observer to get notified on new queries
	__network->add_query_observer( new octoquery_handler( this ) );


}

/**
 * Print an error message into the chatroom
 * @param[in] error_message String message to print
 */
void octomanager::err( std::string error_message )
{
	__main_room->post( octomail( "~ ", __main_room->get_subject(), error_message ) );
}

/**
 * add a new octouser to the room
 * @param[in] user The new octouser to add
 * \todo register the the room owner and then add user in the for everyone
 */
void octomanager::add_user( octouser* user )
{
	try // if ( !( __main_room->name_is_used( user->get_name() ) ) )
	{
		__main_room->add_user( user );
	}
	catch( octoroom_exception exc ) // else
	{
		///std::cerr << exc.what() << endl; \todo log ?
		if ( __user->get_name() == __main_room->get_owner_name() )
		{
			// send the error message to user who try to connect
			octopeer peer( *user->get_peer() );
			octoquery query;
			query.headers_map[ OCTOCHAT_PROTOCOL_ERR ] = OCTOCHAT_ERR_USERNAME_IN_USE;
			query.content_str = exc.what();
			__network->send_query( peer, query ); /// \todo query send ?
		}
	}
}

/**
 * Update the subject of a room
 * @param[in] new_sub The subject for a room
 */
void octomanager::update_subject( std::string new_sub )
{
	__main_room->set_subject( new_sub );
}

/**
 *  Post an new octomail into a room
 * @param[in] mail Message to post
 */
void octomanager::post( octomail mail )
{
	__main_room->post( mail );
}
