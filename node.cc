// Module Node (implementation)
// made by Vincent GHEROLD and Emile CAILLOL
// version 1.3

#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <memory>

#include "node.h"
#include "error.h"
#include "tools.h"
#include "constantes.h"

using namespace std;

namespace {
    vector<Node*> nodeGroup;
};

//========== NodeManager Methods ==========

bool Node::readLine(string line,int type){
    istringstream data(line);
    if (type != LINK){
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
            return false;
        }
        nodeCircle.radius = sqrt(nbp);
        return Node::addNode(nodeCircle,nbp,type,UID);
    } else {
        ID UID1,UID2;
        try {
            string dataToTest;
            data >> dataToTest;
            UID1 = stoi(dataToTest);
    
            data >> dataToTest;
            UID2 = stoi(dataToTest);
        } catch (const std::exception& e){ 
            return false;
        }
        return Node::addLink(UID1,UID2);
    }
}
bool Node::addNode(Circle circle, unsigned int sizePopulation, int type,
                          ID identifier){
                       
    bool success(false);
    Node* pNode(nullptr);
    switch (type){
    case 0:
        pNode = new NodeHousing(circle,sizePopulation,identifier,success);
        break;
    case 1:
        pNode = new NodeTransport(circle,sizePopulation,identifier,success);
    case 2:
        pNode = new NodeProduction(circle,sizePopulation,identifier,success);
        break;
    }
    if (success and pNode != nullptr) nodeGroup.push_back(pNode);

    return success;
}
bool Node::addLink(ID UID1, ID UID2){

    Node* pNode1(pickNodeByUID(UID1)); 
    Node* pNode2(pickNodeByUID(UID2));
    if (pNode1 == nullptr or pNode2 == nullptr) return false;

    if (UID1 == UID2) {
        cout << error::self_link_node(UID1) << endl;
        return false;
    }
    Segment currentSegment = {pNode1->nodeCircle.center, pNode2->nodeCircle.center};
    for (auto& node:nodeGroup){
        if (    node->UID != UID1
            and node->UID != UID2
            and tools::overlapBetweenCircleSegment(node->nodeCircle,currentSegment, 
                                                   dist_min)){
            cout << error::node_link_superposition(node->UID)<< endl;
            return false;
        }
    }

    if(pNode1->checkIfNodeIsAlreadyLinked(*pNode2)) return false;
    if(pNode2->checkIfNodeIsAlreadyLinked(*pNode1)) return false;

    if(pNode1->checkLinksLimit()) return false;
    if(pNode2->checkLinksLimit()) return false;

    pNode1->links.push_back(UID2);
    pNode2->links.push_back(UID1);
    return true;

}
Node* Node::pickNodeByUID(ID UID){
    for (size_t i(0); i < nodeGroup.size(); ++i){
        if ( nodeGroup[i]->UID == UID){
            return nodeGroup[i];
        }
    }
    cout << error::link_vacuum(UID) << endl;
    return nullptr;
}
void Node::showNodeGroup(){
    cout << "--------- nodeGroup -----------" << endl;
    for (auto& node:nodeGroup){
       node->showNode();
    }
}

//========== Node Methods ==========
Node::Node(Circle& circle, unsigned int sizePopulation, ID identifier, 
            bool& success){
     // Check validity of argument
    if (identifier == no_link) {
        cout<< error::reserved_uid() << endl;
        success = false; 
        return;
    }
    if (sizePopulation < min_capacity){
        cout<< error:: too_little_capacity(sizePopulation) << endl;
        success = false; 
        return;
    }
    if (sizePopulation > max_capacity){
        cout<<error:: too_much_capacity(sizePopulation) << endl;
        success = false;
        return;
    }
    for (auto& node:nodeGroup){
        if(node->UID == identifier){
            cout<<error::identical_uid(identifier) << endl;
            success = false;
            return;
        }
        if(tools::overlapBetweenCircles(circle, node->nodeCircle, dist_min)){
           cout<< error::node_node_superposition(identifier,node->UID) << endl;
            success = false;
            return;
        }
    }
    nodeCircle = circle;
    nbp = sizePopulation;
    UID = identifier;
    success = true;
    return;
}

bool Node::checkIfNodeIsAlreadyLinked(Node nodeToCheck) const{
    for (size_t i(0); i < links.size(); ++i){
        if (links[i] == nodeToCheck.UID){
            cout << error::multiple_same_link(UID,nodeToCheck.UID) << endl;
            return true;
        }
    }
    return false;
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
        cout << "   link: " << UID<< " <-> "<<link << endl;
    }
}

void Node::emptyNodeGroup(){
    for (auto& node:nodeGroup){
       delete node;
    }
    nodeGroup.clear();
}
bool Node::checkLinksLimit() const {
    return false;
}
const vector<Node*>& Node::getNodeGroup(){
    return nodeGroup;
};
//================= NodeHousing =================
NodeHousing::NodeHousing(Circle& circle, unsigned int sizePopulation, ID identifier, 
                         bool& success)
:Node(circle,sizePopulation,identifier,success){};

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
//================= NodeTransport =================
NodeTransport::NodeTransport(Circle& circle, unsigned int sizePopulation, 
                             ID identifier, bool& success)
:Node(circle,sizePopulation,identifier,success){};

void NodeTransport::showNode() const {
    this->Node::showNode();
    cout << "Type: Transport" << endl;
    cout << "--------------------" << endl;

}
bool NodeTransport::checkLinksLimit() const {
    return false;
}
//================= NodeProduction =================
NodeProduction::NodeProduction(Circle& circle, unsigned int sizePopulation, 
                               ID identifier, bool& success)
:Node(circle,sizePopulation,identifier,success){};
void NodeProduction::showNode() const {
    this->Node::showNode();
    cout << "Type: Production" << endl;
    cout << "--------------------" << endl;
}
bool NodeProduction::checkLinksLimit() const {
    return false;
}