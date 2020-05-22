// Module City (implementation)
// Made by Vincent GHEROLD and Emile CAILLOL
// Version 2.1
// Architecture b1

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include <iomanip>
#include <cmath>

#include "city.h"
#include "node.h"
#include "error.h"
#include "tools.h"
#include "constantes.h"

using namespace std;

namespace {
	City city;
}

// === Distmin on readfile
#define distMinWhenReadFile 0. 


// === node gestion ===
bool City::readFile(string data) {
	ifstream fichier(data);
	 	
	if(!fichier.fail()) {
		string line;
		int type(-1);
		int compteur(0);
        while(getline(fichier >> ws,line)){	
			if(line[0]=='#') 
				continue; 

			if (compteur == 0){
				compteur = stoi(line);
				++type;
				continue;
			}
			if (compteur > 0){
				if (type == 3 && not city.addLink(line, distMinWhenReadFile)) {
					city.emptyNodeGroup(); 
					return false;
				}
				if (type < 3 && not city.addNode(line,type,distMinWhenReadFile)){
					city.emptyNodeGroup(); 
					return false;
				}
				--compteur;
			}
		}
		cout << error::success();
		return true;

	} else {
		cout << "error opening file" << endl;
		return false;
	}
}
bool City::save(string nom){
	ofstream fichier(nom);
	if(!fichier.fail()) {

		vector<vector<Node*>> nodeGroupSorted;

		nodeGroupSorted.push_back( city.getType(HOUSING)  );
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
	} else 
		return false;
	fichier.close();
	return true;
}
void City::updateDraw(bool shortestPath, Node* selectedNode){
	//draw links
	tools::setColor(BLACK);
	vector<array<Node*,2>> linkCreated;
    for (auto& node:city.nodeGroup){
        node->drawLink(linkCreated,node,true);
    }

	//draw nodes that are not selected
	tools::setColor(BLACK);
	for (auto& node:city.nodeGroup){
		if (node != selectedNode) node->drawNode();
	}
	
	//draw shortestPath to selected node
	tools::setColor(GREEN);
	if (   selectedNode != nullptr 
		&& shortestPath
		&& selectedNode->getType() == HOUSING){
		city.dijkstra(selectedNode->getUID(),TRANSPORT,true);
		city.dijkstra(selectedNode->getUID(),PRODUCTION,true);
	}
	//draw SelectedNode
	tools::setColor(RED);
	if (selectedNode != nullptr) 
		selectedNode->drawNode();
}
void City::emptyNodeGroup(){
    for (auto& node:city.nodeGroup){
       delete node;
    }
    city.nodeGroup.clear();
}
bool City::addNode(Point pos, Type type, double distMin){
	ID newUID(city.findNewUID());
	
	stringstream line("");
	line << newUID << " " << pos.x << " " << pos.y << " " << min_capacity << endl;
	
	return city.addNode(line.str(),type, distMin);
}
bool City::addNode(string line, int type, double distMin){
	Node* pNode(nullptr);
	bool success(false);
	
	switch (type){
	case 0:
		pNode = new NodeHousing(line,type,success,nodeGroup, distMin);
		break;
	case 1:
		pNode = new NodeTransport(line,type,success,nodeGroup, distMin);
		break;
	case 2:
		pNode = new NodeProduction(line,type,success,nodeGroup, distMin);
		break;
	}
	if (pNode == nullptr) return false;
	if (not success or not pNode->checkOneNodeCollisionNodesAndLinks(pNode,
																	 city.nodeGroup)){
		delete pNode;
		return false;
	}
	city.nodeGroup.push_back(pNode);
	return true;
}
bool City::addLink(string line, double distMin){
	ID UID1,UID2;
	
	if (not Node::readLink(line,UID1,UID2)) return false;
	
    Node* pNode1(pickNodeByUID(UID1)); 
    Node* pNode2(pickNodeByUID(UID2));
    if (pNode1 == nullptr or pNode2 == nullptr) return false;
	
    if (UID1 == UID2) {
        cout << error::self_link_node(UID1);
        return false;
    }   
    for (auto& node:nodeGroup){
        if (not (node->checkCollisionNodeLink(pNode1,pNode2,distMin))) 
			return false;
    }
    if (pNode1->checkIfNodeIsAlreadyLinked(pNode2) and
	 	pNode1->checkIfNodeIsAlreadyLinked(pNode2)){
		cout << error::multiple_same_link(pNode1->getUID(),pNode2->getUID());
		return false;
	}
	if (pNode2->checkIfNodeIsAlreadyLinked(pNode1)){
		cout << error::multiple_same_link(pNode2->getUID(),pNode1->getUID());
		return false;	
	}
	
    if(pNode1->checkLinksLimit()) return false;
    if(pNode2->checkLinksLimit()) return false;
	
    if(not pNode1->addLink(pNode2)) return false;
    if(not pNode2->addLink(pNode1)) return false;
    return true;
}
void City::updateLink(Node* nodeToLink1, Node* nodeToLink2, double distMin){
	if (nodeToLink1->checkIfNodeIsAlreadyLinked(nodeToLink2)){	
		nodeToLink1->deleteLink(nodeToLink2);
		nodeToLink2->deleteLink(nodeToLink1);
		return;
	}
	stringstream line("");
	line << nodeToLink1->getUID() << " " << nodeToLink2->getUID() << endl;
	city.addLink(line.str(), distMin);
}
void City::deleteNode(Node* nodeToDelete){
	for (auto& node:city.nodeGroup) node->deleteLink(nodeToDelete);
	for (auto& node:city.nodeGroup){
		if (node == nodeToDelete){			
			
			delete nodeToDelete;
			nodeToDelete = nullptr;
			swap(node,city.nodeGroup.back());
			city.nodeGroup.pop_back();
			break;

		}
	}
	return;
}
void City::moveNode(Point newPos, Node* nodeToMove){
	if (nodeToMove == nullptr) return;
	
	//change position to perform tests
	Point formerPos(nodeToMove->getPos());
	nodeToMove->changeNodeCoordinates(newPos);

	if (not nodeToMove->checkOneNodeCollisionNodesAndLinks(nodeToMove,city.nodeGroup)
		or not nodeToMove->checkLinksOfNodeOverlap(nodeToMove, city.nodeGroup))
		nodeToMove->changeNodeCoordinates(formerPos);
}
void City::resizeNode(Node* node, Point firstPos, Point lastPos){
	
	double startRadius( tools::distance(node->getPos(), firstPos) );
	double endRadius( tools::distance(node->getPos(),lastPos) );
	
	double currentRadius( sqrt(node->getNbp()) );

	double newNbp( pow( currentRadius +(endRadius-startRadius) ,2) );
	City::resizeNode(newNbp,node);
}
void City::resizeNode(double newNbp, Node* nodeToResize){
	if (nodeToResize == nullptr) return;
	
	double formerNbp(nodeToResize->getNbp());
	nodeToResize->changeNodeNbp(newNbp);
	if (not nodeToResize->checkOneNodeCollisionNodesAndLinks(nodeToResize,
															 city.nodeGroup))
		nodeToResize->changeNodeNbp(formerNbp);
}
void City::showNodeGroup() const {
    cout << "--------- nodeGroup -----------" << endl;
    for (auto& node:nodeGroup){
       node->showNode();
	}
}
Node* City::getClickedNode(Point pos,Node* selectedNode){
	return Node::selectNode(pos,selectedNode,city.nodeGroup);
}
ID City::findNewUID(){

	ID testedUID(0);
	size_t index(0);
	
	while (index < nodeGroup.size()){
		
		if (testedUID == nodeGroup[index]->getUID()){
			index = 0;
			++testedUID;
		} else ++index;
	}
	return testedUID;
}

// === criteria ===
string City::criteriaENJ(){
	double dayNbpTotal(0);
	double restNbpTotal(0);
	if (city.nodeGroup.empty()) 
		return to_string(dayNbpTotal);
	
	for (size_t i(0); i < city.nodeGroup.size(); ++i){
		double currentNbp (city.nodeGroup[i]->getNbp());
		Type currentType (city.nodeGroup[i]->getType());
		dayNbpTotal += currentNbp;
		if (currentType == HOUSING) 
			restNbpTotal += currentNbp;
		else restNbpTotal -= currentNbp;
	}
	stringstream balance("");
	balance << setprecision(4) << restNbpTotal/dayNbpTotal;
	return balance.str();
}
string City::criteriaCI(){
	if (city.nodeGroup.empty()) 
		return "0";
	vector<array<Node*,2>> linkCreated(city.getLinkGroup());
	
	double cost(0);
	for (size_t i(0); i < linkCreated.size(); ++i){
		
		double distance (linkCreated[i][0]->dist(linkCreated[i][1]));
		
		double capacity ( min((linkCreated[i][0]->getNbp()),
				(linkCreated[i][1]->getNbp())) );
				
		double speed(1);
		if (linkCreated[i][0]->getType() == TRANSPORT and
			linkCreated[i][1]->getType() == TRANSPORT)
			speed = fast_speed;
		else speed = default_speed;
		
		cost += (distance*capacity*speed);
	}
	stringstream value(" ");
	value << cost;
	return value.str();
}
string City::criteriaMTA(){
	if (city.nodeGroup.empty()) 
		return "0";
	int sizeHousing(0);
	double accessTime(0);

	for (auto node:city.nodeGroup){
		if (node->getType() == HOUSING){
			++sizeHousing;
			accessTime += city.dijkstra(node->getUID(),TRANSPORT,false);
			accessTime += city.dijkstra(node->getUID(),PRODUCTION,false);
		}
	}
	if (sizeHousing == 0)
		return "0";

	stringstream mean("");
	mean << accessTime/sizeHousing;
	return mean.str();
}

// === Dijstra function ===
double City::dijkstra(ID startNodeID, Type type, bool showPath){
	
	//Je fais une copie de surface des pointeurs du tableau de noeuds.
	//Donc j'aurai deux tableaux qui pointent vers mes noeuds
	//car mon algorithme dijkstra mélange mon tableau de noeuds copiés.
	vector<Node*> nodeGroupMTA(city.nodeGroup);
	for (auto node:nodeGroupMTA) node->initNodeDijkstra(startNodeID);
	
	Node::sortNodeGroup(nodeGroupMTA, startNodeID);
	
	Node* findedNode(Node::dijkstra(nodeGroupMTA, type));

	if (findedNode != nullptr){
		if (showPath)
			Node::drawSortestPath(findedNode);
		return findedNode->getAccess();
	}
	return infinite_time;
}

// === tools functions ===
Node* City::pickNodeByUID(ID UID) const {
    for (size_t i(0); i < nodeGroup.size(); ++i){
        if ( nodeGroup[i]->getUID() == UID)
            return nodeGroup[i];
    }
    cout << error::link_vacuum(UID);
    return nullptr;
}
vector<Node*> City::getType(Type type) const{
	vector<Node*> output;
	for (auto& node:city.nodeGroup){
		if (node->getType() == type) 
			output.push_back(node);
	}
	return output;
}
vector<array<Node*,2>> City::getLinkGroup() const{
	vector<array<Node*,2>> linkCreated;
	for (auto& node:city.nodeGroup){
		node->drawLink(linkCreated,node,false);
	}
	return linkCreated;
}
