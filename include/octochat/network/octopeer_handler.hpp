#ifndef OCTOPEER_HANDLER_HPP
#define OCTOPEER_HANDLER_HPP

/**
 * @file octopeer_handler.hpp
 *
 * @section desc File description
 *
 * get notified when a new octopeer 
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
#include "octochat/octouser.hpp"
#include "include/octonet/octopeer.hpp"
#include "include/octonet/octonet_manager.hpp"
#include "include/octonet/octopeer_observer.hpp"


class octopeer_handler : public octopeer_observer
{
	private :
		vector< octopeer* > __queued_peers;
	public :
		octopeer_handler( ) :
			__queued_peers( );
		{}
		
		void update_peer( const octopeer &peer, octopeer_state state )
		{
			int i = 0;
			while( i < vector.size() or __queued_peers[ i ] != ? ) /// \todo
			{
			}
		}
}

#endif

