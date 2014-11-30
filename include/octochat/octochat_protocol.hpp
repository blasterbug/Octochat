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
 /// for new users
#define OCTOCHAT_PROTOCOL_NEW_USER "user"
 /// to include username in octoqueries
#define OCTOCHAT_PROTOCOL_USER_NAME "nickname"
 /// when an octo-user is being accepted in a room
#define OCTOCHAT_PROTOCOL_AUTH_OK "accepted"
 /// when an user is rejected from a room
#define OCTOCHAT_PROTOCOL_AUTH_KO "username in used"
 /// for octomails
#define OCTOCHAT_PROTOCOL_MAIL "msg"
 /// when an octo-user quit an octo-room, specialy when he's the owner
#define OCTOCHAT_PROTOCOL_QUIT "quit"
 /// to specify octoroom name for octomails and auth
#define OCTOCHAT_PROTOCOL_DESTINEE "to"
 /// when changing a room subject
#define OCTOCHAT_PROTOCOL_SUBJECT "title"
 /// to specify octorooms owner
#define OCTOCHAT_PROTOCOL_OWNER "owner"
 /// to specify octoroom name
#define OCTOCHAT_PROTOCOL_ROOM "roomname"
 /// for errors, currently useless
#define OCTOCHAT_PROTOCOL_ERR "error"

#endif

