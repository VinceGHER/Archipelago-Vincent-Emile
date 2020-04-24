// Module City (implementation)
// made by Vincent GHEROLD and Emile CAILLOL
// version 1.0

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include <algorithm>

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

bool City::readFile(string data) {
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
		City::save("dd.txt");
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
    for (auto& node:city.nodeGroup){
       delete node;
    }
    city.nodeGroup.clear();
}

string City::convertDoubleToString(const double& value){
	stringstream name("");
	name << value;
	return name.str();
}

// === Criteria ===
string City::criteriaENJ(){
	double dayNbpTotal(0);
	double restNbpTotal(0);
	if (city.nodeGroup.empty()) return to_string(dayNbpTotal);
	
	for (size_t i(0); i < city.nodeGroup.size(); ++i){
		double currentNbp (city.nodeGroup[i]->getNbp());
		Type currentType (city.nodeGroup[i]->getType());
		dayNbpTotal += currentNbp;
		if (currentType == HOUSING)
			restNbpTotal += currentNbp;
		else
			restNbpTotal -= currentNbp;
	}
	double balance(restNbpTotal/dayNbpTotal);
	return city.convertDoubleToString (balance);
}
string City::criteriaCI(){
	if (city.nodeGroup.empty()) return "0";
	vector<array<Node*,2>> linkCreated(city.getLinkGroup());
	
	double cost(0);
	for (unsigned int i(0); i< linkCreated.size(); ++i){
		
		double distance (linkCreated[i][0]->dist(linkCreated[i][1]));

		double capacity (min((linkCreated[i][0]->getNbp()),
				(linkCreated[i][1]->getNbp())));
				
		double speed (1);
		if ((linkCreated[i][1]->getNbp()) == TRANSPORT
			and(linkCreated[i][1]->getNbp())== TRANSPORT)
				speed = fast_speed;
		else
				speed = default_speed;
		
		cost += (distance*capacity*speed);
	}
	
	return city.convertDoubleToString (cost);
}

bool City::initialiseDijkstra(){
	setIn(true);
	setAccess(infinite_time);
	setParent(no_link);
}

double City::dijkstra(int d, Type type){
	city.initialiseDijkstra();
	double n(0);
	while (not city.nodeGroup.empty()){
		n = 1;
		if (city.nodeGroup[n]->getNbp() == type)
			return n;
		node.setIn(false);
		
	return 0;

string City::criteriaMTA(){
	if (city.nodeGroup.empty()) return "0";
	int sizeHousing(0);
	double accessTime(0);
	for (unsigned int i(0); i< city.nodeGroup.size(); ++i){
		if (city.nodeGroup[i]->getType() == HOUSING){
			sizeHousing += 1;
			accessTime += city.dijkstra(i,PRODUCTION);
			accessTime += city.dijkstra(i,TRANSPORT);
	}
	mean = accessTime/sizeHousing;
	return city.convertDoubleToString (mean);
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

// === Save ===
bool City::save(string nom){
	ofstream fichier(nom);
	if(!fichier.fail()) {

		vector<vector<Node*>> nodeGroupSorted;

		nodeGroupSorted.push_back( city.getType(HOUSING) );
		nodeGroupSorted.push_back( city.getType(TRANSPORT) );
		nodeGroupSorted.push_back( city.getType(PRODUCTION) );

		fichier << "#generated by program" << endl << endl;
		for (auto& nodesSorted:nodeGroupSorted){
			fichier << nodesSorted.size() << endl;
			for (auto& node:nodesSorted){
				node->saveNode(fichier);
			}
		}

		vector<array<Node*,2>> linkCreated(city.getLinkGroup());

		fichier << linkCreated.size() << endl;
		for (auto& link:linkCreated){
			fichier << "\t" << link[0]->getUID() << " " << link[1]->getUID() << endl;
		}
	} else return false;
	fichier.close();
	return true;
}
vector<Node*> City::getType(Type type){
	vector<Node*> output;
	for (auto& node:city.nodeGroup){
		if (node->getType() == type) output.push_back(node);
	}
	return output;
}
vector<array<Node*,2>> City::getLinkGroup(){
	vector<array<Node*,2>> linkCreated;
	for (auto& node:city.nodeGroup){
		node->getVectorLink(linkCreated,node);
	}
	return linkCreated;
}
