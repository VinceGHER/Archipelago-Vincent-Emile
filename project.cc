// Projet (fichier maitre)
// made by Vincent GHEROLD and Emile CAILLOL
// version 1.0

#include <iostream>
#include <vector>
#include "city.h"
using namespace std;

int main(int argc, char * argv[])
{
	if(argc != 2) exit(0);
	else {
		City::lecture(argv[1]);
		string success();
	}
	return 0;
}
