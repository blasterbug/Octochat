#ifndef QUERY_HANDLER_HPP
#define QUERY_HANDLER_HPP

/**
 * @file query_handler.hpp
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
#include "include/octonet/octopeer.hpp"
#include "include/octonet/octonet_manager.hpp"
#include "include/octonet/octoquery.hpp"
#include "include/octonet/octoquery_observer.hpp"
#include "include/octonet/octonet.hpp"
#include "octochat_protocol.hpp"

/**
 * Class to observ query from octoweb
 */
class query_handler : public octoquery_observer {
	private :
		octomanager* __manager; /// the octoroom for the session
	public :
		query_handler( const octomanager* manager  ) :
			__manager( manager )
			{}
			
		void update_query( const octoquery &data ) {
			/// \todo change it to be more flexible and EXPANDABLE
			string query = data[ OCTONET_APP_ID_HEADER ];
			if ( OCTOCHAT_PROTOCOL_MAIL == query )
			{
				__manager->post( octomail( data[ OCTOCHAT_PROTOCOL_USER_NAME ],
									data[ OCTOCHAT_PROTOCOL_DESTINEE ],
									data[ OCTOCHAT_PROTOCOL_CONTENT ] )
				);
				
			}
			else if ( OCTOCHAT_PROTOCOL_NEW_USER == query )
			{
				// add the new user
				octopeer user_peer( data[ OCTONET_IP_ADDRESS_HEADER ],
									data[ OCTONET_TCP_PORT_HEADER ] );
				__manager->add_user( octouser( data[ OCTOCHAT_PROTOCOL_USER_NAME ], user_peer ) );
			}
			else if ( OCTOCHAT_PROTOCOL_ERR == query )
				__manager->err( data[ OCTOCHAT_PROTOCOL_ERR ] );
			else
				__manger->err( data[ query ] );
		}
		
		std::string app() const {
			return OCTONET_APP_ID_HEADER;
		} 

}

#endif
