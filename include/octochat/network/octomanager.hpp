#ifndef OCTOCHAT_MANAGER_HPP
#define OCTOCHAT_MANAGER_HPP
/**
 * @file octomanager.hpp
 *
 * @section desc File description
 *
 * file to manage network query from octonet
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
#include "octonet/octopeer.hpp"
#include "octonet/octoquery.hpp"
#include "octonet/octonet.hpp"
#include "octochat/octoroom.hpp"
#include "octochat/octouser.hpp"
#include "octochat/octomail.hpp"
#include "octcchat/network/octoquery_handler.hpp"

/***
 * Class to link the chat to the octonetwork
 * Basically :
 * 	- get update by query_handler,
 * 	- update local room (adding/removing octouser, messaging, etc.),
 * 	- manager errors
 */
class octomanager
{
	private :
		octoroom* __main_room; /// Main room to manager \todo several rooms
		octouser* __user; /// user for the current session
		octonet* __network; /// octonet objet to communicate over the LAN

	public :
		/**
		 * Octomanager contructor
		 * @param[in] room Room to manage
		 * @param[in] user Octouser for the session
		 * @param[in] network Octonet object for communication
		 */ 
		octomanager( octoroom* room, octouser* user, octonet* network ) :
			__main_room( room ),
			__user( user),
			__network( network )
		{
			__network->add_peer_observer( octoquery_handler( this ) );
		}

		void err( std::string error_message )
		{
			__main_room->post( octomail( "~ ", __main_room->get_subject(), error_message );
		}

		/**
		 * add a new octouser to the room
		 * @param[in] user The new octouser to add
		 * \todo register the the room owner and then add user in the for everyone
		 */
		void add_user( octouser* user )
		{
			try // if ( !( __main_room->name_is_used( user->get_name() ) ) )
			{
				__main_room->add_user( user );
			}
			catch( octoroom_exception exc ) // else 
			{
				///std::cerr << exc.what() << endl; \todo log ?
				if ( __user == __main_room->get_owner )
				{
					octopeer peer( user->get_peer() );
					octoquery query();
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
		void update_subject( std::string new_sub )
		{
			__main_room->set_subject( new_sub );
		}
};

#endif
