/**
 * @file octomail.hpp
 *
 * @section desc File description
 *
 * header for message class
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

#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>
#include "octouser.hpp"
#include "octoroom.hpp"

class octomail {

	private:
		user __from; /// Whoe send the message?
		room __destination; /// Where the message should be posted?
		std::string __content; /// Content of the message, i.e. text bitch!
		int __timeStmp; /// When the message was created? (local time)

	public:
		octomail(const user &writer, const room &adressee, std::string text):
			__from(writer),
			__destination(adressee),
			__content(text),
			__timeStmp(0) /// TODO
		{}

};

#endif
