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
#include "constantes.h"

using namespace std;

namespace {
	City city;
}


// === Node Gestion ===

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
				if (type == 3 && not city.addLink(line)) {
					city.emptyNodeGroup(); 
					return false;
				}
				if (type < 3 && not city.addNode(line,type)){
					city.emptyNodeGroup(); 
					return false;
				}
				--compteur;
			}
		}
		city.showNodeGroup();
		cout << error::success() << endl;

		//Node::getNodeGroup()[0]->showNode();

		//city.emptyNodeGroup();

		return true;

	} else return false;
}
bool City::addNode(string line, int type){
	Node* pNode(nullptr);
	bool success(false);
	//cout << "line: " << line << " type: " << type << endl;
	switch (type){
		case 0:
			pNode = new NodeHousing(line,type,success,nodeGroup);
			break;
		case 1:
			pNode = new NodeTransport(line,type,success,nodeGroup);
			break;
		case 2:
			pNode = new NodeProduction(line,type,success,nodeGroup);
			break;
	}
	if (pNode == nullptr) return false;
	if (not success) return false;
	// if (not pNode->readLine(line,type,nodeGroup)){
	// 	delete pNode;
	// 	return false;
	// }

	city.nodeGroup.push_back(pNode);
	return true;
}
bool City::addLink(string line){

	ID UID1,UID2;

	if (not Node::readLink(line,UID1,UID2)) return false;

    Node* pNode1(pickNodeByUID(UID1)); 
    Node* pNode2(pickNodeByUID(UID2));
    if (pNode1 == nullptr or pNode2 == nullptr) return false;

    if (UID1 == UID2) {
        cout << error::self_link_node(UID1) << endl;
        return false;
    }
   
    for (auto& node:nodeGroup){
        if (not (node->checkCollisionNodeLink(pNode1,pNode2))) return false;
    }

    if(pNode1->checkIfNodeIsAlreadyLinked(pNode2)) return false;
    if(pNode2->checkIfNodeIsAlreadyLinked(pNode1)) return false;

    if(pNode1->checkLinksLimit()) return false;
    if(pNode2->checkLinksLimit()) return false;


    if(not pNode1->addLink(pNode2)) return false;
    if(not pNode2->addLink(pNode1)) return false;
    return true;

}
Node* City::pickNodeByUID(ID UID) const {
    for (size_t i(0); i < nodeGroup.size(); ++i){
        if ( nodeGroup[i]->getUID() == UID){
            return nodeGroup[i];
        }
    }
    cout << error::link_vacuum(UID) << endl;
    return nullptr;
}
void City::showNodeGroup() const {
    cout << "--------- nodeGroup -----------" << endl;
    for (auto& node:nodeGroup){
       node->showNode();
    }
}
void City::emptyNodeGroup(){
    for (auto& node:nodeGroup){
       delete node;
    }
    nodeGroup.clear();
}


// === Critere ===
double City::CriteriaENJ(){
	
	
	vector<double> liste = {};
	//~ for (int(i); i < 5; ++i){
		//~ liste.push_back(Node::getNodeGroup());
	//~ }
	
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
double City::CriteriaCI(){
	vector<double> liste{1,2,3,4};
	vector<vector<int>> liens{{1,2},{1,4},{3,2}};
	
	//for (unsigned int i(0); i< liens.size(); ++i){
	return 0;
}


// === Drawing ====
void City::updateDraw(){
	//draw Links
	vector<ID> linkCreated;
    for (auto& node:city.nodeGroup){
        node->drawLink(linkCreated);
    }

	//draw Nodes
	for (auto& node:city.nodeGroup){
		node->drawNode();
	}
	    

}