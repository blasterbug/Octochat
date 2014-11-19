#ifndef OCTOPRETER_HPP
#define OCTOPRETER_HPP

/**
 * @file octopreter.hpp
 *
 * @section desc File description
 *
 * inpretor pattern to perform command in octochat
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

#include <map>
#include <string>
#include "octouser.hpp"
#include "octomail.hpp"

/**
 * Abstract class for interpretor pattern
 */
class abstract_expression {
	public:
		/** Member function to call in the express tree
		 * @param[in] octoroom contexte of the command
		 * @param[in] string arguments of the command
		 */
		virtual void interpret( const octoroom*, std::string ) = 0 ;
};

/**
 * Abstract class for final_expression in interpretor
 */
class final_expression : abstract_expression {
	public:
		final void interpret( const octoroom*std::string ) = 0 ;
};

/**
 * Class for non terminal expression in the tree
 */
class non_terminal_expression : abstract_expression {
	protected:
		/// sub tree in the intreprator tree
		std::map< std::string, abstract_expression > __subexp;

	public:
		final void interpret( const octoroom*, std:string  ) = 0;
};

/**
 * Class for post mail command
 */
class post_mail : final_expression {
	private:
		const octouser* __sender;
	public:
	/**
	 * constructeur for post mail command
	 * @param[in] userfrom from who the mail is send
	 */
		post_mail( coutuser userfrom ) :
			__sender( userfrom )
			{};

		void interpret( const octoroom *room, std::string input ){
			octomail to_send( user, room, input );
			room->post( message );
		};
}

 #endif
