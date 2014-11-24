#include <iostream>
#include "octonet/octonet.hpp"
#include "octochat/octoroom.hpp"
#include "octochat/octouser.hpp"
#include "octochat/octomail.hpp"
//#include "octochat/network/octoquery_handler.hpp"

#include <ncurses.h> /// \todo !! :)


using namespace std;

int main( int argc, char** argv ) {

	octouser alice( "Alice", 0 );
	octoroom sallon( &alice, "alice alone" );
	
	octonet net();
	//octomanager manager( &sallon, &alice, &net );
	//net.run();

	octouser bob( "Bob", 0 );
	sallon.add_user( &bob );

	sallon.post( octomail( "Alice", "alice alone", "blblblbl" ) );
	sallon.post( octomail( "Bob", "alice alone", "blblblbl" ) );
	
	cout << sallon.to_string() << endl;
	return 0;
}
