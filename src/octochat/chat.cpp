#include "octouser.hpp"
#include "octoroom.hpp"
#include "octomail.hpp"
#include <octonet/octopeer.hpp>

#include <iostream>

using namespace std;

int main( int argc, char** argv ) {

	octouser alice( "Alice", 0 );
	octoroom sallon( &alice, "alice alone" );
	sallon.add_user( &alice );

	octouser bob( "Bob", 0 );
	sallon.add_user( &bob );

	sallon.post( octomail( "Alice", "alice alone", "blblblbl" ) );
	sallon.post( octomail( "Bob", "alice alone", "blblblbl" ) );
	
	cout << sallon.to_string() << endl;
	return 0;
}
