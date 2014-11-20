#include "octouser.hpp"
#include "octomail.hpp"
#include "octoroom.hpp"
#include <octonet/octopeer.hpp>

#include <iostream>

using namespace std;

int main(int argc, char** argv ) {
	octouser	alice( "Alice" );
	octoroom sallon( &alice, "alice alone" );
	octomail mail( alice, sallon, "bonjour alice");
	sallon.post( &mail );
	return 0;
}

