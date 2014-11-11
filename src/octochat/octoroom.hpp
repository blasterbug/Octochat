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
#include <boost/assign/std/vector.hpp> // for 'operator+=()'
#include <boost/assign/list_inserter.hpp>
#include "octouser.hpp"

using namespace std;

/**
 * Exceptions throwed by octoroom class
 */
class octoroom_exception : std::exception {
	private:
		char* _cause; /** store exception description */
	public:
		/** constructor
		 * @param[in] cause description of exception origin
		 */
		octoroom_exception(char* cause):
			_cause(cause)
			{}

		/** destructor
		 * currently, do anything special
		 */
		virtual ~octoroom_exception() throw(){
			// do nothing
		}

		/** virtual fonction from superclass,
		 * usefull to get the exception description
		 */
		virtual const char* what()const throw(){
			return _cause;
		}
};

/**
 * An octo-room is the place where octo-users chat
 */
class octoroom {

	private:
		user __creator /// Who created the room ? -Can be a ghost
		vector<octouser*> __userlist; /// Who is in the room? // TODO : use a map
		vector<octouser*> __bannedusers; /// Who is not allowed here // TODO : use a map !
		string __subject; /// subject of the room


	public:

		/**
		 * Contructor for octo-room
		 * @param[in] owner The octo-user who created the room
		 * @param[in] title The subject of the room
		 */
		octoroom( user &owner, string title ) :
			__creator( owner ),
			__subject( title ),
			__userlist(),
			__bannedusers();
		{}

		/**
		 * Adding user in the room
		 * @param[in] user User to add in the room
		 */
		void addUser(const ocotouser &user) throw octoroom_exception {
			// ?
		}



};

#endif
