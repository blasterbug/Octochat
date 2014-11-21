/**
 * @file octouser.hpp
 *
 * @section desc File description
 *
 * inplementation file for octouser class
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


/**
 * Create a new user
 * @param[in] name (Nick)name of the user
 * @param[in] peer object for an user
 */
octouser::octouser( std::string name, const octopeer *peer) :
	__name( name ),
	__peer( peer ),
	__alive( false )
{}

/**
 * Copy contructor, make a copy of the object
 * @param[in] tocopy Octo-user to copy
 */
octouser::octouser( const octouser& tocopy ) :
	__name( tocopy.__name ),
	__peer( tocopy.__peer ),
	__alive( tocopy.__alive )
	{}

/**
 * What is the name of the user ?
 * @param[out] Name of the user
 */
std::string octouser::get_name() const {
	return __name;
}

/**
 * Is the user online ?
 * @param[out] True if the user is online, else false is returned
 */
bool octouser::is_online() const {
	return __alive;
}
