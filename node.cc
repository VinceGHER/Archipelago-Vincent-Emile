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

namespace {
    std::vector<Node> nodeGroup;
}

bool Node::readLine(string line,int type){
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

bool Node::addNode(Circle circle, unsigned int sizePopulation, 
                   int t,ID identifier){
                       
    bool success(false);
    Node currentNode(circle,sizePopulation,t,identifier,success);

    if (success) nodeGroup.push_back(currentNode);

    return success;
}
Node::Node(Circle& circle, unsigned int sizePopulation, int t, ID identifier, 
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
};


// ======== Create Link ======
bool Node::addLink(ID UID1, ID UID2){

    Node* pNode1(pickNodeByUID(UID1)); 
    Node* pNode2(pickNodeByUID(UID2));
    if (pNode1 == nullptr or pNode2 == nullptr) return false;
   
    Segment currentSegment = {pNode1->nodeCircle.center, pNode2->nodeCircle.center};
    for (auto& node:nodeGroup){
        if (    node.UID != UID1 
            and node.UID != UID2 
            and tools::overlapBetweenCircleSegment(node.nodeCircle,currentSegment, 
                                                   dist_min)){
            cout << error::node_link_superposition(node.UID)<< endl;
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
     if (links.size() >= max_link){
        cout << error::max_link(UID) << endl;
        return true;
    }
    return false;
}


// ======= Usefull Method =====
Node* Node::pickNodeByUID(ID UID){
    for (size_t i(0); i < nodeGroup.size(); ++i){
        if (nodeGroup[i].UID == UID){
            return &nodeGroup[i];
        }
    }
    cout << error::link_vacuum(UID) << endl;
    return nullptr;
}
void Node::showNodeGroup(){
    cout << "--------- nodeGroup -----------" << endl;
    for (auto node:nodeGroup){
        cout <<"UID: " << node.UID << endl;
        cout << "CenterX: " << node.nodeCircle.center.x << " " 
             << "CenterY: " << node.nodeCircle.center.y << " "
             << "Radius: " << node.nodeCircle.radius << endl;
        cout <<"Type: " << node.type << endl;
        cout << "Links: (" << node.links.size()<< ")" <<  endl;
        for (auto lien:node.links){
            cout << "   link: " << node.UID<< " <-> "<<lien << endl;
        }
        cout << "--------------------" << endl;
    }
}
