#include "octouser.hpp"
#include "octomail.hpp"
#include "octoroom.hpp"
#include <octonet/octopeer.hpp>

#include <iostream>

using namespace std;

int main(int argc, char** argv ) {
	octouser	alice( "Alice" );
	octoroom sallon( &alice, "alice alone" );
	octomail* mail = new octomail( alice, sallon, "bonjour");
	sallon.post( mail );
	mail = new octomail( alice, sallon, "il y a quelqu'un alice");
	sallon.post( mail );
	cout << sallon.to_string() << endl;
	return 0;
}
