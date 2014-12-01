#ifndef OCTOBSERVER_HPP
#define OCTOBSERVER_HPP
/**
 * @file octobserver.hpp
 *
 * @section desc File description
 *
 * header file for octo-observers, design pattern by GoF
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

#include "octochat/octostate.hpp"

/**
 * class to define an observer object
 */
class octobserver
{
	public:
		/// get updated from the observable object
		virtual void update( octostates_name state ) = 0 ;
};

#endif
