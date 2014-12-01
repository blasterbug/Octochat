#ifndef OCTOQUERY_HANDLER_HPP
#define OCTOQUERY_HANDLER_HPP

/**
 * @file octoquery_handler.hpp
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

#include <iostream>
#include <string>
#include <map>
#include <boost/lexical_cast.hpp> // for string to unsigned short
#include <boost/asio.hpp> // for string to ip

#include "octonet/octopeer.hpp"
#include "octonet/octonet_manager.hpp"
#include "octonet/octoquery.hpp"
#include "octonet/octoquery_observer.hpp"
#include "octonet/octonet.hpp"

#include "octochat.hpp"
#include "octochat/octochat_protocol.hpp"
#include "octochat/octomanager.hpp"
#include "octochat/octosession.hpp"

#include <iostream>

/**
 * Class to observ query from octonetwork
 */
class octoquery_handler : public octoquery_observer
{
	private :
		octomanager* __manager; /// the octoroom for the session
		octosession* __session; /// the current session

	public :
		/**
		 * Constructor for Octoquery handlers
		 * @param[in] manager Octomanger to notify when receiving a new query
		 * @param[in] session The current session
		 */
		octoquery_handler( octomanager* manager, octosession* session ) :
			__session( session ),
			__manager( manager )
		{}

		/**
		 *  Member function called when a new octoqueries arrive
		 */
		void update_query( const octoquery &query )
		{
			// get the query type
			std::string header = query.headers_map.find( OCTOCHAT_PROTOCOL_HEADER )->second;
			std::cout << header << std::endl;
			// the query is a message to post
			if ( OCTOCHAT_PROTOCOL_MAIL == header )
			{
				__manager->post( octomail( query.headers_map.find( OCTOCHAT_PROTOCOL_USER_NAME )->second,
									query.headers_map.find( OCTOCHAT_PROTOCOL_DESTINEE )->second,
									query.content_str ) );
			}
			// the query is an authentication confirmation
			else if ( OCTOCHAT_PROTOCOL_AUTH_OK == header )
			{
				octopeer* owner_peer = new octopeer( boost::asio::ip::address::from_string( query.headers_map.find( OCTONET_IP_ADDRESS_HEADER )->second),
									boost::lexical_cast<unsigned short>(query.headers_map.find( OCTONET_TCP_PORT_HEADER )->second ));
				octouser* owner = new octouser( query.headers_map.find( OCTOCHAT_PROTOCOL_OWNER )->second, owner_peer );
				// start local room
				__manager->open_local_octoroom( owner, OCTOCHAT_PROTOCOL_ROOM );
				__session->edit_nickname( query.content_str );
				__session->connect();
			}
			// the query is to noticied user can't be connected
			else if ( OCTOCHAT_PROTOCOL_AUTH_KO == header )
			{
				__session->disconnect();
			}
			// the query is a new user
			else if ( OCTOCHAT_PROTOCOL_NEW_USER == header )
			{
				// create the octouser from the query
				octopeer* user_peer = new octopeer( boost::asio::ip::address::from_string( query.headers_map.find( OCTONET_IP_ADDRESS_HEADER )->second),
									boost::lexical_cast<unsigned short>(query.headers_map.find( OCTONET_TCP_PORT_HEADER )->second ));
				octouser* new_user = new octouser( query.content_str, user_peer );
				// boolean to user adding confirmation
				bool added = false;
				// add the new user
				try {
					__manager->add_user( new_user );
					added = true;
				}
				// user name is already used
				catch( octoroom_exception exp )
				{
					added = false;
				}
				std::cout << __session->get_nickname() << new_user->get_name() << std::endl;
				// if the owner is the local user
				if ( __manager->get_room_owner_name() == new_user->get_name()
					|| __session->get_nickname() == new_user->get_name() )
				{
					// send a query to the user to tell him he can be connected (or not)
					__session->notify_user_auth( new_user, added );
				}
			}
			// subject room update query
			else if ( OCTOCHAT_PROTOCOL_SUBJECT == header )
			{
				__manager->update_subject( query.content_str );
			}
			// the query is a weird, tread it like an error
			else
			{
				__manager->post( octomail( "ERROR", OCTOCHAT_DEFAULT_ROOM_NAME, query.content_str ) );
			}
		}

		/**
		 * Function member called when when handler is regestered to query observable
		 * @return App ID for the handler
		 */
		std::string app() const
		{
			return OCTONET_APP_ID_HEADER;
		}

};

#endif
