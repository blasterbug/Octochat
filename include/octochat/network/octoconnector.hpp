#ifndef OCTOCONNECTOR_HPP
#define OCTOCONNECTOR_HPP

/**
 * @file octomanager.cpp
 *
 * @section desc File description
 *
 * file to manage connexion for a new user
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

/**
 * Octoconnector provide a simple way for get a user to be connected
 * or not, depending if the choosen name is already used or not
 */
 class octoconnecter
 {
	 private:
	 /// the server to comunicate
		octonet* __server;
		/// get an updated list of peers on the network
		octopeer_handler* __octopeer_handler;
		public:
		/**
		 * Constructor
		 * @param[in] server The octonet to use for communication
		 */
		octoconnecter( octonet* server ) :
			__server( server )
		{
			__server->add_peer_observer( octopeer_handler() );
		}
		/**
		 * registered an user to the octonetwork
		 * @param[in] name The choosen name for the user
		 * @param[out] true if connected, else false
		 */
		bool registered_user( string name )
		{
			/// get the peers to
		}
};
#endif
