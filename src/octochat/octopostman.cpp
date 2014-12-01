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

#include "octochat/octochat_protocol.hpp"

/**
 * Constructor
 * @param[in] server The octonet to use for communication
 * @param[in] session The current session
 */
octopostman::octopostman( octonet* server, octosession* session ) :
	__server( server )
{
	__server->add_peer_observer( this );
}

/**
 * Get notified when new peers are connected to the octonetwork
 * @param[in] peer The new peer arrived to store
 * @param[in] state State of the new peer, currently useless
 */
void octopostman::update_peer(const octopeer& peer, octopeer_state state){
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
void octopostman::register_user( std::string name, std::string room_name)
{
	// if there is not other peer
	if( 2 < __connected_peers.size() )
	{
		__session->connect_as_owner();
	}
	else
	{
		// create a query to send to every peer connected
		// to get the user registered into the other room(s)
		octoquery query;
		// add app id in headers
		query.headers_map[ OCTONET_APP_ID_HEADER ] = OCTONET_APP_ID_HEADER;
		// add query type
		query.headers_map[ OCTOCHAT_PROTOCOL_HEADER] = OCTOCHAT_PROTOCOL_NEW_USER;
		// add user name in headers
		query.headers_map[ OCTOCHAT_PROTOCOL_NEW_USER ] = name;
		// add room name in headers
		query.headers_map[ OCTOCHAT_PROTOCOL_DESTINEE ] = room_name;
		// send the query for each peers connected
		__send_query( query );
	}
	// créer la room local et le octuser local
}

/**
 * Send an octomail over the octonetwork
 * @param[in] mail he mail to send
 */
void octopostman::send( octomail mail)
{
	// create a new query to send
	octoquery query;
	// add the right app id
	query.headers_map[ OCTONET_APP_ID_HEADER ] = OCTONET_APP_ID_HEADER;
	// add query type
		query.headers_map[ OCTOCHAT_PROTOCOL_HEADER] = OCTOCHAT_PROTOCOL_MAIL;
	// add the writer name in the header
	query.headers_map[ OCTOCHAT_PROTOCOL_NEW_USER] = mail.get_writer_name();
	// add the destinee
	query.headers_map[ OCTOCHAT_PROTOCOL_MAIL ] = mail.get_destinee();
	// add content
	query.content_str = mail.get_content();
	// final send the query
	__send_query( query);
}
