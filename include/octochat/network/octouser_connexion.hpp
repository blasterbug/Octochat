#ifndef OCTOUSER_CONNECTION_HPP
#define OCTOUSER_CONNECTION_HPP

/**
 * @file octouser_connection.hpp
 *
 * @section desc File description
 *
 * file to manage octo-user to get connected to an octo-room
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
 * @date 2014/11/15
 * @author Benjamin Sientzoff
 * @version 0.1
 */

#include <string>
#include <map>

#include <boost/asio.hpp>

#include "include/octonet/octonet.hpp"
#include "include/octonet/octopeer.hpp"
#include "include/octonet/octoquery.hpp"

#include "include/octochat/network/octopeer_handler.hpp"
 
/**
 * Class to get an user authentihied into an octo-room
 */
class octouser_connexion {
	private :
		octonet* __server;
		
	public :

	/**
	 * Constructor
	 * @param[in] server Server for octnetwork communication
	 */
	octouser_connexion(octonet* server) :
		__server( server )
	{
		octonet->add_peer_observer( octoquery_handler( this ) );
	}
	
	/**
	 * Register the user with a name into the ocotnetwork
	 * @param[in] name Name of the user
	 * @param[in] server Server to use for registration
	 * @param[out] true if the user is registered, else false
	 */
	bool registered_user( string name, octonet* server )
	{
		std::set<octopeer, octopeer_comparator> peers();
		__server->peers(peers)
		
	}
};

#endif
