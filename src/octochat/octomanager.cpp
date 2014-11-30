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
//#include "octochat/octoquery_handler.hpp"

/**
 * Octomanager contructor
 * @param[in] session The current session
 */
octomanager::octomanager()
	//__session( session )
{
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
	__main_room->set_subject( new_sub );
}

/**
 *  Post an new octomail into a room
 * @param[in] mail Message to post
 */
void octomanager::post( octomail mail )
{
	__main_room->post( mail );
}
