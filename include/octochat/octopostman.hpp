#ifndef OCTOPOSTMAN_HPP
#define OCTOPOSTMAN_HPP

/**
 * @file octopostman.hpp
 *
 * @section desc File description
 *
 * header file for the octopostman object
 * Define a simple way to send query over the octonetwork
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
#include <map>

#include <boost/asio.hpp>

#include "octonet/octoquery.hpp"
#include "octonet/octopeer.hpp"
#include "octonet/octonet_manager.hpp"
#include "octonet/octopeer_observer.hpp"
#include "octonet/octonet.hpp"
#include "octonet/octonet_manager.hpp"

#include "octochat.hpp"
#include "octochat/octochat_protocol.hpp"

/**
 * Octopost provides a simple way to send messages over the octonetwork
 * Octopost postman is also usefull for octouser connection
 * \todo : user a factory to build queries?
 */
 class octopostman : octopeer_observer
 {
	 private:
	 /// the server to comunicate
		octonet* __server;
		/// set to store connected peers on the network
		std::set< octopeer, octopeer_comparator > __connected_peers;

		/**
		 * function to send a query for each peer connected
		 * @param[in] query The octoquery to send to peers
		 */
		void __send_query( octoquery query)
		{
			// for each peers connected
			for(std::set< octopeer, octopeer_comparator >::const_iterator it = __connected_peers.begin(); it != __connected_peers.end() ; ++it)
			{
				// send data over Octonetwork
				__server->send_query( *it, query );
			}
		}

		public:
		/**
		 * Constructor
		 * @param[in] server The octonet to use for communication
		 */
		octopostman( octonet* server ) :
			__server( server )
		{
			__server->add_peer_observer( this );
		}

		/**
		 * Get notified when new peers are connected to the octonetwork
		 * @param[in] peer The new peer arrived to store
		 * @param[in] state State of the new peer, currently useless
		 */
		void update_peer(const octopeer& peer, octopeer_state state){
			if ( online == state )
			{
				// currently erase two peers with the same ip address
				__connected_peers.insert( peer );
			}
			else
			{
				__connected_peers.erase( peer );
			}
		}

		/**
		 * register an user to the octonetwork
		 * @param[in] name The choosen nickname for the user
		 * @param[in] room_name The room to be connected in
		 */
		void register_user( std::string name, std::string room_name)
		{
			// if there is not other peer
			if( __connected_peers.empty() )
			{
				// at least the user peers should be there !
				// force broadcast to update peers
				__server->send_broadcast( OCTONET_DEFAULT_UDP_PORT );
			}
			else
			{
				// create a query to send to every peer connected
				// to get the user registered into the other room(s)
				octoquery query;
				// add app id in headers and put query type as value
				query.headers_map[ OCTONET_APP_ID_HEADER ] = OCTONET_APP_ID_HEADER;
				// add query type
				query.headers_map[ OCTOCHAT_PROTOCOL_HEADER ] = OCTOCHAT_PROTOCOL_NEW_USER;
				// add user name in headers
				query.headers_map[ OCTOCHAT_PROTOCOL_NEW_USER ] = name;
				// and in content
				query.content_str = name;
				// add room name in headers
				query.headers_map[ OCTOCHAT_PROTOCOL_ROOM ] = room_name;
				// send the query for each peers connected
				__send_query( query );
			}
		}

		/**
		 * Send an octomail over the octonetwork
		 * @param[in] mail he mail to send
		 */
		void send( octomail mail)
		{
			// create the new query to send
			octoquery query;
			// add the right app id
			query.headers_map[ OCTONET_APP_ID_HEADER ] = OCTONET_APP_ID_HEADER;
			// add the query type in headers
			query.headers_map[ OCTOCHAT_PROTOCOL_HEADER ] = OCTOCHAT_PROTOCOL_MAIL;
			// add the writer name in headers
			query.headers_map[ OCTOCHAT_PROTOCOL_NEW_USER] = mail.get_writer_name();
			// add the destinee
			query.headers_map[ OCTOCHAT_PROTOCOL_ROOM ] = mail.get_destinee();
			// add content
			query.content_str = mail.get_content();
			// finally send the query
			__send_query( query );
		}

		/**
		 * The query to send when a new user is connected in a room
		 * @param[in] user Approved octo-user
		 * @param[in] owner The room owner name
		 */
		void send_auth_ok( octouser* user, std::string owner )
		{
			// create the new query to send
			octoquery query;
			// add the right app id
			query.headers_map[ OCTONET_APP_ID_HEADER ] = OCTONET_APP_ID_HEADER;
			// add the query type in headers
			query.headers_map[ OCTOCHAT_PROTOCOL_HEADER ] = OCTOCHAT_PROTOCOL_AUTH_OK;
			// add room owner in headers
			query.headers_map[ OCTOCHAT_PROTOCOL_OWNER] = owner;
			// add content
			query.content_str = user->get_name();
			// finally send the query
			__server->send_query( *(user->get_peer()), query );
		}

		/**
		 * send a query to noticed a user he can't joint an octo-room
		 * @param[in] user Rejected octo-user
		 */
		void send_auth_ko( octouser* user )
		{
			// create the new query to send
			octoquery query;
			// add the right app id
			query.headers_map[ OCTONET_APP_ID_HEADER ] = OCTONET_APP_ID_HEADER;
			// add the query type in headers
			query.headers_map[ OCTOCHAT_PROTOCOL_HEADER ] = OCTOCHAT_PROTOCOL_AUTH_KO;
			// add user's name in content
			query.content_str = user->get_name();
			// finally send the query to octopeer
			__server->send_query( (*user->get_peer()), query );
		}

};
#endif
