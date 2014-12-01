#ifndef OCTO_SUBJECT_HPP
#define OCTO_SUBJECT_HPP
/**
 * @file octo_subject.hpp
 *
 * @section desc File description
 *
 * header file for subjects objects, design pattern by GoF
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
 * @date 2014/11/30
 * @author Benjamin Sientzoff
 * @version 0.1
 */

#include <set>

#include "octochat/octobserver.hpp"
#include "octochat/octostate.hpp"

/**
 * class to define an observable object
 */
class octo_subject
{
	protected:
		/// store observers
		std::set< octobserver* > __observers;
	public:
		/// contructor
		octo_subject() :
			__observers()
		{}
		/**
		 * Add a new observer
		 * @param[in] observer The new observer to notify
		 */
		void add_octobserver( octobserver* observer )
		{
			__observers.insert( observer );
		}
		/**
		 * Remove an observer
		 * @param[in] observer Observer to remove
		 */
		void remove_octobserver( octobserver* observer )
		{
			__observers.erase( observer );
		}
		/// notify octobservers
		void notify( octostates_name state )
		{
			for ( std::set< octobserver* >::iterator it = __observers.begin() ; it != __observers.end(); ++it )
			{
				(*it)->update( state );
			}
		}
};

#endif
