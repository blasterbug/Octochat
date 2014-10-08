/**
 * @file message.hpp
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

class message {

	private:
		user from_; /// Whoe send the message?
		room destination_; /// Where the message should be posted?
		string content_; /// Content of the message, i.e. text bitch!
		int timeStmp_; /// When the message was created? (local time)

	public:
		message(const &user writer, room adressee, string text):
			from_(writer),
			destination_(adresse),
			content_(text),
			timeStmp_(0) /// TODO
		{};

};
