#ifndef OCTOSTATES_HPP
#define OCTOSTATES_HPP

/**
 * @file octostates.cpp
 *
 * @section desc File description
 *
 * The state design pattern to represent the state of the current session
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

#include <string>

#include "octonet/octonet.hpp"

#include "octochat/octouser.hpp"
#include "octochat/octomail.hpp"
#include "octochat/octoroom.hpp"

#include "octochat/network/octochat_protocol.hpp"
#include "octochat/octostate/session.hpp"

/**
 * Class to represent a state
 */
class octostate
{
	private:
		/// the current session
		octosession* __session;
	public:
		/**
		 * Constructor, virtual to be abstract
		 * @param[in] session the current session
		 */
		virtual octostate( octosession* session) = 0;
		/// connection transition
		void connect(){}
		/// deconnection transition
		void disconnect(){}
		/// waiting transition
		void wait(){}
};

/**
 * connected state class
 */
class connected_octostate : public octostate
{
	public:
		/**
		 * constructor
		 * @param[in] session The current session
		 */
		connected_octostate( octosession* session ) :
			__session( session )
		{}

		/**
		 * The only reachable transition when session is connected is deconnection
		 */
		void disconnect()
		{
			__session->set_current_state( __session->get_deconnected_state() );
		}
};

/// deconnected state class
class deconnected_octostate : public octostate
{
	public:
			/**
		 * constructor
		 * @param[in] session The current session
		 */
		disconnected_octostate( octosession* session ) :
			__session( session )
		{}
		/// The only one transition to pass
		void wait()
		{
			__session->set_current_state( __session->get_waitting_state() );
		}
};

/// waiting state
class waiting_octostate : public octostate
{
	public:
			/**
		 * constructor
		 * @param[in] session The current session
		 */
		waiting_octostate( octosession* session ) :
			__session( session )
		{}
		/// function to pass from waiting state to deconnected state
		void disconnect()
		{
			__session->set_current_state( __session->get_deconnected_octostate() );
		}
		/// function to pass from waiting state to connected state
		void connect()
		{
			__session->set_current_state( __session->get_connected_octostate() );
		}
};

#endif
