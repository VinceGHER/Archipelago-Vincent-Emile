// Module Node (implementation)
// made by Vincent GHEROLD and Emile CAILLOL
// version 1.3

#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <memory>
#include <algorithm>


#include "node.h"
#include "error.h"
#include "tools.h"
#include "constantes.h"

using namespace std;

//========== Node Methods ==========

Node::Node(string line,int type,bool& success,vector<Node*>& nodeGroup){
    istringstream data(line);
    ID UID; 
    Circle nodeCircle; 
    unsigned int nbp; 
    try {
        //stoul() convert string to unsigned long
        //stoi() convert string to int
        string dataToTest;
        data >> dataToTest;
        UID = stoul(dataToTest);
        
        data >> dataToTest;
        nodeCircle.center.x = stoi(dataToTest);

        data >> dataToTest;
        nodeCircle.center.y = stoi(dataToTest);

        data >> dataToTest;
        nbp = stoul(dataToTest);

    } catch (const std::exception& e){ 
        success = false;
        return;
    }
    nodeCircle.radius = sqrt(nbp);
    if (not verifyNodeParameter(nodeCircle,nbp,UID, nodeGroup)){
        success = false;
        return;
    }
    success = true;
}
bool Node::readLink(string line,ID& UID1,ID& UID2){
    istringstream data(line);
    try {
        string dataToTest;
        data >> dataToTest;
        UID1 = stoi(dataToTest);

        data >> dataToTest;
        UID2 = stoi(dataToTest);
    } catch (const std::exception& e){ 
        return false;
    }
    return true;
}
bool Node::addLink(Node* nodeToLink){
    if (nodeToLink == nullptr) return false;
    links.push_back(nodeToLink);
    return true;
}
const ID Node::getUID() const{
    return UID;
}
void Node::showNode() const {
    cout <<"UID: " << UID << endl;
    cout << "CenterX: " << nodeCircle.center.x << " " 
            << "CenterY: " << nodeCircle.center.y << " "
            << "Radius: " << nodeCircle.radius << endl;
    cout << "Links: (" << links.size()<< ")" <<  endl;
    for (auto link:links){
        cout << "   link: " << UID<< " <-> "<<link->UID << endl;
    }
}

// === Draw functions ===
void Node::drawNode() const{
    tools::drawCircle(nodeCircle);
}
void Node::drawLink(vector<ID>& linkCreated) {		
    for (auto& link:links){
        if (not (std::find(linkCreated.begin(), linkCreated.end(), link->UID) 
            != linkCreated.end()) ){

            Point start(nodeCircle.center);
            Point end  (link->nodeCircle.center);
            tools::drawSegment(Segment{start,end});
            linkCreated.push_back(link->UID);
        }
    }
   
}


// === Verification method ===
bool Node::verifyNodeParameter(Circle& circle, unsigned int sizePopulation, 
                               ID identifier,vector<Node*>& nodeGroup){
     // Check validity of argument
    if (identifier == no_link) {
        cout<< error::reserved_uid() << endl; 
        return false;
    }
    if (sizePopulation < min_capacity){
        cout<< error:: too_little_capacity(sizePopulation) << endl;
        return false;
    }
    if (sizePopulation > max_capacity){
        cout<<error:: too_much_capacity(sizePopulation) << endl;
        return false;
    }
    for (auto& node:nodeGroup){
        if(node->UID == identifier){
            cout<<error::identical_uid(identifier) << endl;
            return false;
        }
        if(tools::overlapBetweenCircles(circle, node->nodeCircle, dist_min)){
           cout<< error::node_node_superposition(identifier,node->UID) << endl;
            return false;
        }
    } 
    nodeCircle = circle;
    nbp = sizePopulation;
    UID = identifier;
    return true;
}
bool Node::checkCollisionNodeLink(Node* pNode1,Node* pNode2){
    Segment currentSegment = {pNode1->nodeCircle.center, pNode2->nodeCircle.center};
    if (UID != pNode1->UID
        and UID != pNode2->UID
        and tools::overlapBetweenCircleSegment(nodeCircle,currentSegment, 
                                                dist_min)){
            cout << error::node_link_superposition(UID)<< endl;
            return false;
        }
    return true;
}
bool Node::checkIfNodeIsAlreadyLinked(Node* nodeToCheck) const{
    for (size_t i(0); i < links.size(); ++i){
        if (links[i]->UID == nodeToCheck->UID){
            cout << error::multiple_same_link(UID,nodeToCheck->UID) << endl;
            return true;
        }
    }
    return false;
}


//================= NodeHousing =================
NodeHousing::NodeHousing(string line,int type, bool& success,vector<Node*>& nodeGroup)
:Node(line,type,success,nodeGroup){}

void NodeHousing::showNode() const {
    this->Node::showNode();
    cout << "Type: Housing" << endl;
    cout << "--------------------" << endl;
}
bool NodeHousing::checkLinksLimit() const {
    if (this->links.size() >= max_link){
        cout << error::max_link(UID) << endl;
        return true;
    }
    return false;
}
void NodeHousing::drawNode() const {
   Node::drawNode();
}


//================= NodeTransport =================
NodeTransport::NodeTransport(string line,int type, bool& success,vector<Node*>& nodeGroup)
:Node(line,type,success,nodeGroup){}

void NodeTransport::showNode() const {
    this->Node::showNode();
    cout << "Type: Transport" << endl;
    cout << "--------------------" << endl;
}
bool NodeTransport::checkLinksLimit() const {
    return false;
}
void NodeTransport::drawNode() const {
    Node::drawNode();
}


//================= NodeProduction =================
NodeProduction::NodeProduction(string line,int type, bool& success,vector<Node*>& nodeGroup)
:Node(line,type,success,nodeGroup){}

void NodeProduction::showNode() const {
    this->Node::showNode();
    cout << "Type: Production" << endl;
    cout << "--------------------" << endl;
}
bool NodeProduction::checkLinksLimit() const {
    return false;
}
void NodeProduction::drawNode() const {
    Node::drawNode();
}
