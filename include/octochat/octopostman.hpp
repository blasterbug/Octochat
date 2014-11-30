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

#include "octochat.hpp"
#include "octochat/octochat_protocol.hpp"

/**
 * Octopost provides a simple way to send messages over the octonetwork
 * Octopost postman is also usefull for octouser connection
 */
 class octopostman : octopeer_observer
 {
	 private:
	 /// the server to comunicate
		octonet* __server;
		/// the current session
		//const octosession* __session;
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
				//__session->connect();
			}
			else
			{
				// create a query to send to every peer connected
				// to get the user registered into the other room(s)
				octoquery query;
				// add app id in headers
				query.headers_map[ OCTONET_APP_ID_HEADER ] = OCTONET_APP_ID_HEADER;
				// add user name in headers
				query.headers_map[ OCTOCHAT_PROTOCOL_NEW_USER ] = name;
				// add room name in headers
				query.headers_map[ OCTOCHAT_PROTOCOL_DESTINEE ] = room_name;
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
			// create a new query to send
			octoquery query;
			// add the right app id
			query.headers_map[ OCTONET_APP_ID_HEADER ] = OCTONET_APP_ID_HEADER;
			// add the writer name in the header
			query.headers_map[ OCTOCHAT_PROTOCOL_NEW_USER] = mail.get_writer_name();
			// add the destinee
			query.headers_map[ OCTOCHAT_PROTOCOL_MAIL ] = mail.get_destinee();
			// add content
			query.content_str = mail.get_content();
			// final send the query
			__send_query( query );
		}

};
#endif
