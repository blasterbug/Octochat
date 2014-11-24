#ifndef OCTOQUERY_HANDLER_HPP
#define OCTOQUERY_HANDLER_HPP

/**
 * @file octoquery_handler.hpp
 *
 * @section desc File description
 *
 * file to manage network query from octonet
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

#include <iostream>
#include <string>
#include <map>
#include "octonet/octopeer.hpp"
#include "octonet/octonet_manager.hpp"
#include "octonet/octoquery.hpp"
#include "octonet/octoquery_observer.hpp"
#include "octonet/octonet.hpp"
#include "octochat/octouser.hpp"
#include "octochat/network/octochat_protocol.hpp"
#include "octochat/network/octomanager.hpp"

/**
 * Class to observ query from octoweb
 */
class octoquery_handler : public octoquery_observer
{
	private :
		octomanager* __manager; /// the octoroom for the session
		
	public :
		/**
		 * Constructor for Octoquery handlers
		 * @param[in] manager Octomanger to notify when receiving a new query
		 */
		octoquery_handler( octomanager* manager  ) :
			__manager( manager )
		{}

		/**
		 *  Member function called when a new octoqueries arrive
		 */
		void update_query( const octoquery &query )
		{
			/// \todo change it to be more flexible and EXPANDABLE
			std::string header = query.headers_map[ OCTONET_APP_ID_HEADER ];
			// the query is a message to post
			if ( OCTOCHAT_PROTOCOL_MAIL == header )
			{
				__manager->post( octomail( query.headers_map[ OCTOCHAT_PROTOCOL_USER_NAME ],
									query.headers_map[ OCTOCHAT_PROTOCOL_DESTINEE ],
									query.content_str )
				);
				
			}
			// the query is  new user
			else if ( OCTOCHAT_PROTOCOL_NEW_USER == header )
			{
				// add the new user
				octopeer user_peer( query.headers_map[ OCTONET_IP_ADDRESS_HEADER ],
									query.headers_map[ OCTONET_TCP_PORT_HEADER ] );
				__manager->add_user( octouser( query.content_str, user_peer ) );
			}
			// subject room update query
			else if ( OCTOCHAT_PROTOCOL_SUBJECT == header )
				__manager->update_subject( query.content_str );
			// the query is an error
			else if ( OCTOCHAT_PROTOCOL_ERR == header )
				__manager->err( query.content_str );
			// the query is a weird, tread it like an error
			else
				__manager->err( query.content_str );
		}

		/**
		 * Function member called when when handler is regestered to query observable
		 * @return App ID for the handler
		 */
		std::string app() const
		{
			return OCTONET_APP_ID_HEADER;
		} 

};

#endif
