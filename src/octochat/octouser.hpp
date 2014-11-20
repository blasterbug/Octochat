#ifndef OCTOUSER_HPP
#define OCTOUSER_HPP

/**
 * @file octouser.hpp
 *
 * @section desc File description
 *
 * header for octouser class
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
 * @date 2014/10/07
 * @author Benjamin Sientzoff
 * @version 0.1
 */


#include <string>
#include "octonet/octopeer.hpp"

class octouser {

	private:
		std::string __name; /// user (unique) name
		const octopeer* __peer; /// "connect" to user
		bool __alive; /// Is the user on/offline ?

	public:
		octouser(){};
		/// constructor for octo-user
		octouser( std::string name, const octopeer *peer);
		/// copy constructor for octo-user
		octouser( const octouser& tocopy );
		/// get the name of the octo-user
		std::string get_name() const;
		/// Is the user online ?
		bool is_online() const;
};

#include "octouser.cpp"

#endif
