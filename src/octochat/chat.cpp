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

//#include <ncurses.h> /// \todo !! :)


using namespace std;

int main( int argc, char** argv )
{
	string en;
	
	//octoroom sallon;
	//octouser usr;
	
	octonet net;
	
	//octomanager manager( 0, 0, &net );
	
	net.run();
	
	cin >> en;
	//cout << sallon.to_string() << endl;
	return 0;
}
