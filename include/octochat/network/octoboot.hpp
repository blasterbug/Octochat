#ifndef OCTOBOOT_HPP
#define OCTOBOOT_HPP
/**
 * @file octoboot.hpp
 *
 * @section desc File description
 *
 * Header file for octochat connexion object
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
#include "octonet/octopeer.hpp"
#include "octonet/octoquery.hpp"
#include "octonet/octonet.hpp"
#include "octonet/octoquery_observer.hpp"

#include "octochat/octoroom.hpp"
#include "octochat/octouser.hpp"
#include "octochat/octomail.hpp"

/***
 * Class to allow a new octouser to be connected into a room
 */
class octoboot
{
	private :
		std::string __usr_name;
		octopeer* __usr_peer;
		octonet* __network;

	public :
		/// \todo
};

#endif
