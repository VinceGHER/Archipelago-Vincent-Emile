// Module Node (implementation)
// made by Vincent GHEROLD and Emile CAILLOL
// version 1.0

#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

#include "node.h"
#include "error.h"
#include "tools.h"
#include "constantes.h"

using namespace std;

//========== NodeManager Methods ==========

bool NodeManager::readLine(string line,int type){
    istringstream data(line);
    if (type != LINK){
        ID UID; 
        Circle nodeCircle; 
        unsigned int nbp; 
        try {
            string dataToTest;
            data >> dataToTest;
            UID = stoi(dataToTest);

            data >> dataToTest;
            nodeCircle.center.x = stoi(dataToTest);

            data >> dataToTest;
            nodeCircle.center.y = stoi(dataToTest);

            data >> dataToTest;
            nbp = stoi(dataToTest);

        } catch (const std::exception& e){ 
            return false;
        }
        nodeCircle.radius = sqrt(nbp);
        return NodeManager::addNode(nodeCircle,nbp,type,UID);
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
        return NodeManager::addLink(UID1,UID2);
    }
}
bool NodeManager::addNode(Circle circle, unsigned int sizePopulation, 
                   int t,ID identifier){
                       
    bool success(false);
    Node currentNode(circle,sizePopulation,t,identifier,success, nodeGroup);

    if (success) nodeGroup.push_back(currentNode);

    return success;
}
bool NodeManager::addLink(ID UID1, ID UID2){

    Node* pNode1(pickNodeByUID(UID1)); 
    Node* pNode2(pickNodeByUID(UID2));
    if (pNode1 == nullptr or pNode2 == nullptr) return false;
    cout << "Nodemanganer" << pNode1->getUID() << " " << pNode2->getUID() << endl;
    if (pNode1->createLinkNode(*pNode2, nodeGroup)){
        return true;
    }
    return false;
}
Node* NodeManager::pickNodeByUID(ID UID){
    for (size_t i(0); i < nodeGroup.size(); ++i){
        if (nodeGroup[i].getUID() == UID){
            return &nodeGroup[i];
        }
    }
    cout << error::link_vacuum(UID) << endl;
    return nullptr;
}
void NodeManager::showNodeGroup(){
    cout << "--------- nodeGroup -----------" << endl;
    for (auto node:nodeGroup){
       node.showNode();
    }
}

//========== Node Methods ==========
Node::Node(Circle& circle, unsigned int sizePopulation, int t, ID identifier, 
            bool& success, const vector<Node>& nodeGroup){
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
        if(node.UID == identifier){
            cout<<error::identical_uid(identifier) << endl;
            success = false;
            return;
        }
        if(tools::overlapBetweenCircles(circle, node.nodeCircle, dist_min)){
           cout<< error::node_node_superposition(identifier,node.UID) << endl;
            success = false;
            return;
        }
    }
    nodeCircle = circle;
    nbp = sizePopulation;
    type = t;
    UID = identifier;
    success = true;
    return;
}
bool Node::createLinkNode(Node& other, const vector<Node>& nodeGroup){

    Segment currentSegment = {nodeCircle.center, other.nodeCircle.center};
    for (auto& node:nodeGroup){
        if (    node.UID != UID 
            and node.UID != other.UID 
            and tools::overlapBetweenCircleSegment(node.nodeCircle,currentSegment, 
                                                   dist_min)){
            cout << node.UID << " " << UID << endl;
            cout << error::node_link_superposition(node.UID)<< endl;
            return false;
        }
    }

    if(checkIfNodeIsAlreadyLinked(other)) return false;
    if(other.checkIfNodeIsAlreadyLinked(*this)) return false;

    if(checkLinksLimit()) return false;
    if(other.checkLinksLimit()) return false;

    links.push_back(other.UID);
    other.links.push_back(UID);
    return true;

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
bool Node::checkLinksLimit() const{
     if (links.size() >= max_link and type == HOUSING){
        cout << error::max_link(UID) << endl;
        return true;
    }
    return false;
}
ID Node::getUID(){
    return UID;
}
void Node::showNode() const {
    cout <<"UID: " << UID << endl;
    cout << "CenterX: " << nodeCircle.center.x << " " 
            << "CenterY: " << nodeCircle.center.y << " "
            << "Radius: " << nodeCircle.radius << endl;
    cout <<"Type: " << type << endl;
    cout << "Links: (" << links.size()<< ")" <<  endl;
    for (auto link:links){
        cout << "   link: " << UID<< " <-> "<<link << endl;
    }
    cout << "--------------------" << endl;
}