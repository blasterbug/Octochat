/**
 * @file room.hpp
 *
 * @section desc File description
 *
 * header for room class
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
 * @date 2014/10/16
 * @author Benjamin Sientzoff
 * @version 0.1
 */

#ifndef OCTOROOM_HPP
#define OCTOROOM_HPP

#include <vector>
#include <string>
#include "octouser.hpp"

class octoroom {

	private:
		user __creator /// Who created the room ? -Can be a ghost
		std::vector<octouser*> __userlist; /// Who is in the room?
		std::string __subject; /// subject of the room

	public:
		octoroom(user &owner, std::string title):
			__creator(owner),
			__subject(title),
			__userlist()
		{}

};

#endif
