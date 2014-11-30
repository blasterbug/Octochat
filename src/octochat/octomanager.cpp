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

#include "octochat.hpp"
#include "octochat/octomanager.hpp"

/**
 * Octomanager contructor
 */
octomanager::octomanager()
{}

/**
 * open the local octo-room
 * @param[in] owner owner of the room
 * @param[in] name The name of the joined octo-room
 */
void octomanager::open_local_octoroom( octouser* owner, std::string name )
{
	__main_room = new octoroom( owner, name );
}

/**
 * Get the name of the room owner
 * @param[out] Name of the octoroom owner
 */
std::string octomanager::get_room_owner_name()
{
	return __main_room->get_owner_name();
}
/**
 * add a new octouser to the room
 * @param[in] user The new octouser to add
 */
void octomanager::add_user( octouser* user )
{
		__main_room->add_user( user );
}

/**
 * Update the subject of a room
 * @param[in] new_sub The subject for a room
 */
void octomanager::update_subject( std::string new_sub )
{
	//__main_room->set_subject( new_sub );
}

/**
 *  Post an new octomail into a room
 * @param[in] mail Message to post
 */
void octomanager::post( octomail mail )
{
	__main_room->post( mail );
}
