#ifndef OCTOMAIL_HPP
#define OCTOMAIL_HPP

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

#include <string>
#include "octouser.hpp"
#include "octoroom.hpp"

/**
 * Octomail is a message send by an octouser into an octoroom
 */
class octomail {

	private:
		octouser __from; /// Whoe send the message?
		const octoroom* __destination; /// Where the message should be posted?
		std::string __content; /// Content of the message, i.e. text bitch!
		int __timeStmp; /// When the message was created? (local time)

	public:

		/// Constructor for octomail
		octomail( octouser&, octoroom*, std::string );
		/// copy constructor for octomail
		octomail( const octomail& );
		/// get the name of the mail writer
		const std::string get_writer_name() const;
		/// get the string reprensentation of the mail
		const std::string to_string() const;
};

#include "octomail.cpp"
#endif
