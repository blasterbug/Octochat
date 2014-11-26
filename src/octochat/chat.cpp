#include <iostream>

#include "octonet/octonet.hpp"
#include "octonet/octopeer.hpp"
#include "octonet/octoquery.hpp"
#include "octonet/octonet.hpp"
#include "octonet/octoquery_observer.hpp"

#include "octochat/octoroom.hpp"
#include "octochat/octouser.hpp"
#include "octochat/octomail.hpp"
#include "octochat/octouser.hpp"
#include "octochat/network/octochat_protocol.hpp"
#include "octochat/network/octomanager.hpp"

#include <boost/asio.hpp>

/// \todo an curses interface
//#include <ncurses.h> 


using namespace std;

/// Ask a nickanme to user
string get_name_id();
/// registered an user to the octonetwork
bool registered_user( string name );

int main( int argc, char** argv )
{
	// start local server
	octonet net;
	net.run();
	string en;

	if ( argc > 1 )
	{
		// user name in parameters
		en = argv[1];
	}
	else
	{
		// if user doesn't give a nickname
		// ask him one
		en = get_name_id();
	}
	// while the username can't be used
	while ( not registered_user( en ) )
	{
		// ask a new one to user
		en = get_name_id();
	}
	//octomanager manager( 0, 0, &net );
	
	//cin >> en;
	//cout << sallon.to_string() << endl;
	return 0;
}

/**
 * Ask to user a nickname for chatting
 * And be sure the name it's not already used
 * @param[out] The name of the user or an empty string if the name entered
 * is not unique.
 */
string get_name_id()
{
	string nickname = "";
	cout << "Please enter a nickname: ";
	cin >> nickname;
	if ( registered_user( nickname ) )
	{
		return nickname;
	}
	else
	{
		cout << nickname << " is already used" << endl;
		return "";
	}
}

/**
 * Register the user with a name into the ocotnetwork
 * @param[in] name Name of the user
 * @param[in] server Server to use for registration
 * @param[out] true if the user is registered, else false
 */
bool registered_user( string name )
{
	
	return false;
}
