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
 * @version 0.2
 */

#include <string>
#include "octochat.hpp"

#define OCTOMANAGER_DEFAULT_OWNER_NAME ""

/***
 * Manage local octorooms from octonetwork
 */
class octomanager
{
	private :
		octoroom* __main_room; /// Main room to manager
		// std::map< std::string, octoroom* > __rooms; \todo several rooms

	public :
		/// Octomanager contructor
		octomanager();
		/// initiate the local octo-room
		void open_local_octoroom( octouser* , std::string );
		/// get the name of the room owner
		std::string get_room_owner_name();
		/// add a new octouser to the room
		void add_user( octouser* );
		/// Update the subject of a room
		void update_subject( std::string );
		/// Post an new octomail into a room
		void post( octomail );
};

#endif
