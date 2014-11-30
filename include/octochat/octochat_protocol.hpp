#ifndef OCTOCHAT_PROTOCOL_HPP
#define OCTOCHAT_PROTOCOL_HPP
/**
 * @file octochat_protocol.hpp
 *
 * @section desc File description
 *
 * Header file for cotochat protocol words
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
 * @date 2014/11/10
 * @author Benjamin Sientzoff
 * @version 0.1
 */


/**
 * Define octochat protocol words
 */

/// headers for query
#define OCTOCHAT_PROTOCOL_NEW_USER "user"
#define OCTOCHAT_PROTOCOL_USER_NAME "nickname"
#define OCTOCHAT_PROTOCOL_AUTH_OK "accepted"
#define OCTOCHAT_PROTOCOL_AUTH_KO "username in used"
#define OCTOCHAT_PROTOCOL_MAIL "msg"
#define OCTOCHAT_PROTOCOL_DESTINEE "to"
#define OCTOCHAT_PROTOCOL_SUBJECT "title"
#define OCTOCHAT_PROTOCOL_OWNER "owner"
#define OCTOCHAT_PROTOCOL_ROOM "roomname"
#define OCTOCHAT_PROTOCOL_ERR "error"

#endif

