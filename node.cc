// Module Node (implementation)
// made by Vincent GHEROLD and Emile CAILLOL
// version 1.0

#include "node.h"
#include "error.h"
#include "tools.h"
#include "constantes.h"

#include <vector>

#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
using namespace std;

namespace {
    std::vector<Node> nodeGroup;
}
bool Node::read(string line,Type type){
    istringstream data(line);
    if (type != LINK){
        ID UID; Circle nodeCircle; unsigned int nbp; 
        try {
            string test;
            data >> test;
            UID = stoi(test);

            data >> test;
            nodeCircle.center.x = stoi(test);

            data >> test;
            nodeCircle.center.y = stoi(test);

            data >> test;
            nbp = stoi(test);

        } catch (const std::exception& e){
            return false;
        }
        // if(not ()){ 
        //     cout << UID << " " <<
        //     nodeCircle.center.x<< " " 
        //     <<nodeCircle.center.y<< " " <<nbp<< " "<<endl;;
        //     return false;
        // }
        nodeCircle.radius = sqrt(nbp);
        return Node::addNode(nodeCircle,nbp,type,UID);
    } else {
        ID UID1,UID2;
        try {
            string test;
            data >> test;
            UID1 = stoi(test);
    
            data >> test;
            UID2 = stoi(test);
        } catch (const std::exception& e){
            return false;
        }
    // if (not (data >> UID1 >> UID2)) return false;
        return Node::addLink(UID1,UID2);
    }
}
Node::Node(Circle circle, unsigned int sizePopulation, Type t, ID identifier)
        :nodeCircle(circle),nbp(sizePopulation),type(t),UID(identifier){};

bool Node::addNode(Circle circle, unsigned int sizePopulation, 
                   Type t,ID identifier){
    // control check
        //est ce qu'il faut faire vérification en dehors de la zone?
    if (identifier == no_link) {
        cout<< error::reserved_uid() << endl;
        return false;
    }
    if (sizePopulation < min_capacity){
        cout<<error:: too_little_capacity(sizePopulation) << endl;
        return false;
    }
    if (sizePopulation > max_capacity){
        cout<<error:: too_much_capacity(sizePopulation) << endl;
        return false;
    }
    for (auto& node:nodeGroup){
        if(node.UID == identifier){
            cout<<error::identical_uid(identifier) << endl;
            return false;
        }
        if(tools::overlapBetweenCircles(circle, node.nodeCircle, dist_min)){
           cout<< error::node_node_superposition(identifier,node.UID) << endl;
            return false;
        }
    }

    Node currentNode(circle,sizePopulation,t,identifier);
    nodeGroup.push_back(currentNode);

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
bool Node::addLink(ID UID1, ID UID2){
    size_t n1Index(0),n2Index(0);
    if(not pickNodeIndex(UID1,n1Index)) return false;
    if(not pickNodeIndex(UID2,n2Index)) return false;
    
    Node &node1 (nodeGroup[n1Index]);
    Node &node2 (nodeGroup[n2Index]);

    if (UID1 == UID2){
        cout << error::self_link_node(UID1) << endl;
        return false;
    }
 
    Segment currentSegment = {node1.nodeCircle.center, node2.nodeCircle.center};
    for (auto& node:nodeGroup){
        if (    node.UID != UID1 
            and node.UID != UID2 
            and tools::overlapBetweenCircleSegment(node.nodeCircle,currentSegment, 
                                               dist_min)){
            cout << error::node_link_superposition(node.UID)<< endl;
            return false;
        }
    }
    
    if(node1.checkIfNodeIsAlreadyLinked(node2)) return false;
    if(node2.checkIfNodeIsAlreadyLinked(node1)) return false;

    if(node1.checkLinksLimit()) return false;
    if(node2.checkLinksLimit()) return false;
 
    node1.links.push_back(UID2);
    node2.links.push_back(UID1);
    return true;
}
bool Node::pickNodeIndex(ID UID, size_t& nIndex){
    for (size_t i(0); i < nodeGroup.size(); ++i){
        if (nodeGroup[i].UID == UID){
            nIndex = i;
            return true;
        }
    }
    cout << error::link_vacuum(UID) << endl;
    return false;
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
