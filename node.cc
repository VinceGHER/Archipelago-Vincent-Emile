// Module Node (implementation)
// made by Vincent GHEROLD and Emile CAILLOL
// version 1.3

#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <algorithm>


#include "node.h"
#include "error.h"
#include "tools.h"
#include "constantes.h"

using namespace std;

//========== Node Methods ==========

Node::Node(string line,int type,bool& success,const vector<Node*>& nodeGroup){
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

// === Getter functions ===
const ID Node::getUID() const{
    return UID;
}
double Node::getNbp() const {
    return nbp;
}

// === Save functions ===
ostream& Node::saveNode(ostream& fichier) const{
    return fichier << "\t" 
                   << UID << " "
                   << nodeCircle.center.x << " "
                   << nodeCircle.center.y << " "
                   << nbp << endl;
} 
void Node::getVectorLink(vector<array<Node*,2>>& linkCreated,Node* thisNodePtr) const{

    for (auto& link:links){

        array<Node*,2> link1 = {thisNodePtr,link};
        array<Node*,2> link2 = {link,thisNodePtr};

        //test if link1 or link2 already exists
        if (not (std::find(linkCreated.begin(), linkCreated.end(), link1)
            != linkCreated.end())
         && not (std::find(linkCreated.begin(), linkCreated.end(), link2)
            != linkCreated.end()) ){

            linkCreated.push_back(link1);
        }
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
                               ID identifier, const vector<Node*>& nodeGroup){
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
bool Node::checkCollisionNodeLink(Node* pNode1,Node* pNode2) const{
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
NodeHousing::NodeHousing(string line,int type, bool& success,
                         const vector<Node*>& nodeGroup)
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
Type NodeHousing::getType() const {
    return HOUSING;
}


//================= NodeTransport =================
NodeTransport::NodeTransport(string line,int type, bool& success,
                             const vector<Node*>& nodeGroup)
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
    for (double angle(0); angle < 2*M_PI; angle+=M_PI/4.){
        Point pointOnCircle {nodeCircle.center.x + cos(angle)*nodeCircle.radius,
                             nodeCircle.center.y + sin(angle)*nodeCircle.radius};
        Segment segment {nodeCircle.center , pointOnCircle};
        tools::drawSegment(segment);
    }

}
Type NodeTransport::getType() const {
    return TRANSPORT;
}


//================= NodeProduction =================
NodeProduction::NodeProduction(string line,int type, bool& success,
                               const vector<Node*>& nodeGroup)
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
    double diameter( nodeCircle.radius*2);
    Point topLeftCorner {nodeCircle.center.x - (0.75*diameter)/2. ,
                         nodeCircle.center.y + (diameter/16.) };
    Point topRightCorner {nodeCircle.center.x + (0.75*diameter)/2.,
                          nodeCircle.center.y + (diameter/16.) };
    Point bottomLeftCorner {nodeCircle.center.x - (0.75*diameter)/2.,
                          nodeCircle.center.y - (diameter/16.) };
    Point bottomRightCorner {nodeCircle.center.x + (0.75*diameter)/2.,
                          nodeCircle.center.y - (diameter/16.) };
    tools::drawSegment(Segment{topLeftCorner,topRightCorner});
    tools::drawSegment(Segment{topRightCorner,bottomRightCorner});
    tools::drawSegment(Segment{bottomRightCorner,bottomLeftCorner});
    tools::drawSegment(Segment{bottomLeftCorner,topLeftCorner});
}
Type NodeProduction::getType() const {
    return PRODUCTION;
}