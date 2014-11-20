#include "octouser.hpp"
#include "octoroom.hpp"
#include "octomail.hpp"
#include <octonet/octopeer.hpp>

#include <iostream>

using namespace std;

int main( int argc, char** argv ) {

	octouser	alice( "Alice", 0 );
	octoroom sallon( &alice, "alice alone" );

	sallon.post( octomail( alice, &sallon, "Bonjour!" ) );
	sallon.post( octomail( alice, &sallon, "il y a quelqu'un alice" ) );
	sallon.post( octomail( alice, &sallon, "bouh!" ) );

	cout << sallon.to_string() << endl;

	return 0;
}
