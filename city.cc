// Module City (implementation)
// made by Vincent GHEROLD !nd Emile CAILLOL
// version 1.0

#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <string>

#include "city.h"
#include "node.h"
#include "error.h"
#include "tools.h"

using namespace std;

bool City::readFile(char* data) {
	ifstream fichier(data);
	 	
	if(!fichier.fail()) {
		string line;
		int type(-1);
		int compteur(0);
        while(getline(fichier >> ws,line)){	
			if(line[0]=='#') continue; 

			if (compteur == 0){
				compteur = stoi(line);
				++type;
				continue;
			}
			if (compteur > 0){
				if(not Node::readLine(line, type)) return false;
				--compteur;
			}
		}
		Node::showNodeGroup();
		cout << error::success() << endl;
		Node::emptyNodeGroup();
		return true;

	} else return false;
}
