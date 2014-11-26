#ifndef OCTOCHAT_MANAGER_HPP
#define OCTOCHAT_MANAGER_HPP
/**
 * @file octomanager.hpp
 *
 * @section desc File description
 *
 * Header file to manage network query from octonet
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

#include "octonet/octopeer.hpp"
#include "octonet/octoquery.hpp"
#include "octonet/octonet.hpp"
#include "octonet/octoquery_observer.hpp"

#include "octochat/octoroom.hpp"
#include "octochat/octouser.hpp"
#include "octochat/octomail.hpp"

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
		octonet* __network; /// octonet objet to communicate over the LAN
		octoroom* __main_room; /// Main room to manager \todo several rooms
		octouser* __user; /// user for the current session

	public :
		/// Octomanager contructor
		octomanager( octonet* );
		/// Print a error message in chat
		void err( std::string );
		/// add a new octouser to the room
		void add_user( octouser* );
		/// Update the subject of a room
		void update_subject( std::string );
		/// Post an new octomail into a room
		void post( octomail );
};

#endif
