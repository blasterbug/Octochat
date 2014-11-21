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

/**
 * Octomail is a message send by an octouser into an octoroom
 */
class octomail {

	private:
		std::string __from; /// Whoe send the message?
		const std::string __destination; /// Where the message should be posted?
		std::string __content; /// Content of the message, i.e. text bitch!
		int __timeStmp; /// When the message was created? (local time) \todo

	public:
		/**
		 * constructor for a octo-mail
		 * @param[in] writer the emitter of the message
		 * @param[in] adressee Where the mail should be posted ?
		 * @param[in] text content of the message
		 */
		octomail( std::string writer, std::string adressee, std::string text ) :
			__from( writer ),
			__destination( adressee ),
			__content( text ),
			__timeStmp( 0 ) /// TODO
		{}

		/**
		 * copy contructor for octo-mail
		 * @param[in] tocopy octo-mail to be copied
		 */
		octomail( const octomail& tocopy ) :
			__from ( tocopy.__from ),
			__destination( tocopy.__destination ),
			__content( tocopy.__content ),
			__timeStmp( tocopy.__timeStmp )
		{}

		/**
		 * get the string representation of an octouser
		 * @param[out] name of the octo-user
		 */
		const std::string get_writer_name() const {
			return __from;
		}

		/**
		 * get the string representation of the octomail
		 * @param[out] The octomail as a string
		 */
		const std::string to_string() const {
			return __from + " : " + __content;
		}

		/**
		 * get the name of the mail destination
		 * @param[out] destination of the mail
		 */
		const std::string get_destinee() const{
			return __destination;
		}
};

#endif
