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


class query_handler : public octoquery_observer {
	private :
		octoroom* __main_room; /// the octoroom for the session
	public :
		query_handler( const octoroom* room ) :
			__main_room( room )
			{}
			
		void update_query( const octoquery &data ) {
			string query = data[octonet_app_id_header];
			/// \todo datatype | content
		}
		
		std::string app() const {
			return octonet_app_id_header;
		}

}

#endif
