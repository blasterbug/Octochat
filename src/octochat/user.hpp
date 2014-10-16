/**
 * @file user.hpp
 *
 * @section desc File description
 *
 * header for user class
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

class user {

	private:
		std::string id_; /// user (unique) name
		std::string ip_port_; /// address to communicate
		bool alive_; /// Is the user on/offline ?

	public:
	/**
	 * Create a new user
	 * @param id (Nick)name of the user
	 * @param socket User's network address
	 */
		user(std::string id, std::string address):
			id_(id),
			ip_port_(address),
			alive_(false)
		{};

	/**
	 * What is the name of the user ?
	 * @return Name of the user
	 */
		std::string getId(){
			return id_;
		}

		bool isOnline(){
			return alive_;
		}

};
