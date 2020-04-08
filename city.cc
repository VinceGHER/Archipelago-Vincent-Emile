// Module City (implementation)
// made by Vincent GHEROLD and Emile CAILLOL
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
	//	Node::showNodeGroup();
		cout << error::success() << endl;

	//	Node::getNodeGroup()[0]->showNode();

		Node::emptyNodeGroup();

		return true;

	} else return false;
}

double CriteriaENJ(){
	
	
	vector<Node*> liste = Node::getNodeGroup();
	
	if (liste.empty()) return 0;
	
	double a(0);
	double b(0);
	for (unsigned int i(0); i< liste.size(); ++i){
		cout << liste[i] << endl;
		//~ a += ;
		//~ if (liste[i] == 0)
			//~ b += liste[i][1];
		//~ else
			//~ b -= liste[i][1];
	}
	return b/a;
}

double CriteriaCI(){
	vector<double> liste{1,2,3,4};
	vector<vector<int>> liens{{1,2},{1,4},{3,2}};
	
	//for (unsigned int i(0); i< liens.size(); ++i){
	return 0;
}
