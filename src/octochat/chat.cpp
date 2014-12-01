#include <iostream>

#include "octonet/octonet.hpp"
#include "octochat/octosession.hpp"
#include "octochat/octobserver.hpp"

using namespace std;

class octo_ui : public octobserver
{
	private:
	octostates_name __current_session_state;
	octosession* __session;

	public:
	octo_ui( octonet* server ) :
		__current_session_state( deconnected ),
		__session( new octosession( server ) )
	{
		__session->add_octobserver( this );
	}

	void update( octostates_name state)
	{
		if ( deconnected == state )
		{
			cout << "You are now deconnected!" << endl;
		}
		else if ( connected == state )
		{
			cout << __session->get_nickname() << ", you are now connected!" << endl;
		}
		else if (waiting == state )
		{
			cout << "connecting ..." << endl;
		}
		__current_session_state = state;
	}

	void try_connect()
	{
		set_name_id();
		__session->start_session();
	}
	void send( string message )
	{
		__session->send_mail( message );
	}
	/**
	 * Ask to user a nickname for chatting
	 * And be sure the name it's not already used
	 * @param[out] The name of the user or an empty string if the given
	 * name is not unique.
	 */
	void set_name_id()
	{
		string nickname = "";
		cout << "Please enter a nickname: ";
		cin >> nickname;
		__session->set_nickname( nickname );
	}

};

int main( int argc, char** argv )
{
	// start local server
	octonet net;
	net.run();

	octo_ui ui( &net );

	string user_input;

	while ( "exit" != user_input )
	{
		cin >> user_input;
		if ( "connect" == user_input )
		{
			ui.try_connect();
		}
		else
		{
			ui.send( user_input );
		}
	}

	return 0;
}
