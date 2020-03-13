// Module City (implementation)
// made by Vincent GHEROLD !nd Emile CAILLOL
// version 1.0

#include "city.h"
#include "node.h"
#include "error.h"
#include "tools.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

City::void lecture( char * data)
{
	string line;
	int compteur(0);
	ifstream fichier(data);
	 
	for (int type (0); type <= 4; ++type){
		cin >> compteur;
		for (int compteur; compteur >=0; --compteur){
			if(line[0]=='#') continue;
			Node::read(line, type);
		}
	}
}


