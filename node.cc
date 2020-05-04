// Module Node (implementation)
// Made by Vincent GHEROLD and Emile CAILLOL
// Version 2.1
// Architecture b1

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

// === rectange of production node ===
#define ratioRectangleWidth 0.75
#define ratioRectangleHeight 0.125 // (1/8) 

// ========== node methods ==========
Node::Node(string line,int type,bool& success,const vector<Node*>& nodeGroup){
    istringstream data(line);
    ID UID; 
    Circle nodeCircle; 
    unsigned int nbp; 
    try {
        //stoul() convert string to unsigned long
        //stod() convert string to double
        string dataToTest;
        data >> dataToTest;
        UID = stoul(dataToTest);
        
        data >> dataToTest;
        nodeCircle.center.x = stod(dataToTest);

        data >> dataToTest;
        nodeCircle.center.y = stod(dataToTest);

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
    cout << "=== Dijkstra === " << endl;
    cout << "access " << access << endl;
    cout << "in " << in << endl;
    if(parent != nullptr) cout << "parent " << parent->UID << endl;
    else cout << "parent " << "nullptr" << endl;
    
    cout << "===" << endl;
}
double Node::dist(Node* node){
	return tools::distance(nodeCircle.center, node->nodeCircle.center);
}

// === getter functions ===
const ID Node::getUID() const {
    return UID;
}
double Node::getNbp() const {
    return nbp;
}

// === save functions ===
ostream& Node::saveNode(ostream& fichier) const{
    return fichier << "\t" 
                   << UID << " "
                   << nodeCircle.center.x << " "
                   << nodeCircle.center.y << " "
                   << nbp << endl;
} 

// === draw functions ===
void Node::drawNode() const{
    tools::drawCircle(nodeCircle);
}
void Node::drawLink(vector<array<Node*,2>>& linkCreated,Node* thisNodePtr,
                    bool drawing) const{	
    for (auto& link:links){
     
        array<Node*,2> link1 = {thisNodePtr,link};
        array<Node*,2> link2 = {link,thisNodePtr};

        //test if link1 or link2 already exists
        if (not (std::find(linkCreated.begin(), linkCreated.end(), link1)
            != linkCreated.end())
        && not (std::find(linkCreated.begin(), linkCreated.end(), link2)
            != linkCreated.end()) ){
            
            if (drawing){
                Point start(nodeCircle.center);
                Point end  (link->nodeCircle.center);
                tools::drawSegment(Segment{start,end});
            }
           
            linkCreated.push_back(link1);
        }
    }
   
}

//=== Dijkstra functions ===
double Node::dijkstra(vector<Node*>& nodeGroup, Type type){

    while (Node::findMinAccess(nodeGroup) != (size_t)-1){
       
        size_t nodeIndex(Node::findMinAccess(nodeGroup));
       
        if (nodeGroup[nodeIndex]->getType() == type) 
            return nodeGroup[nodeIndex]->access;

        nodeGroup[nodeIndex]->in = false;
        if (nodeGroup[nodeIndex]->getType()==PRODUCTION) continue;
        vector<Node*> currentLinks(nodeGroup[nodeIndex]->links);
  
        for (size_t lv(0); lv < currentLinks.size(); ++lv){
            if (currentLinks[lv]->in){
                
                double alt(nodeGroup[nodeIndex]->access 
                         + computeAccess(nodeGroup[nodeIndex],currentLinks[lv]));
            
                if (currentLinks[lv]->access > alt){
                    currentLinks[lv]->access = alt;
                    currentLinks[lv]->parent = nodeGroup[nodeIndex];
                    sortNodeGroup(nodeGroup, currentLinks[lv]->UID);
                }
            }
        }
    }
    return no_link;
}
void Node::initNodeDijkstra(ID startNodeID){
    in = true;
    access = (startNodeID == UID)? 0 : infinite_time;
    parent = nullptr;

}
void Node::sortNodeGroup(vector<Node*>& nodeGroup, ID UIDToUpdate){
    size_t currentIndex(no_link);
    for (size_t i(0); i < nodeGroup.size(); ++i){
		if (nodeGroup[i]->UID == UIDToUpdate){
            currentIndex = i;
            break;
		}
	}
    bool success(false);
    while (currentIndex > 0 and not success){
        if (nodeGroup[currentIndex]->access <= 
            nodeGroup[currentIndex-1]->access){
            swap(nodeGroup[currentIndex],nodeGroup[currentIndex-1]);
            --currentIndex;
        } else success = true;
    }		
}
size_t Node::findMinAccess(const vector<Node*>& nodeGroup){
    unsigned int minAcess(-1);
    size_t indexNode(-1);
    for (size_t i(0); i < nodeGroup.size(); ++i){
        if (nodeGroup[i]->access < minAcess and nodeGroup[i]->in){
            minAcess = nodeGroup[i]->access;
            indexNode = i;
        }
    }
    return indexNode;
}
double Node::computeAccess(Node* node1, Node* node2){
    double distBetweenNode(node1->dist(node2));
    double speed(0);
    
    if (node1->getType() == TRANSPORT and node2->getType() == TRANSPORT) 
        speed = fast_speed;
    else speed = default_speed;

    return distBetweenNode/speed;
}
void Node::showdijkstra(std::vector<Node*>& nodeGroup){
    for (auto node:nodeGroup){
        cout << "---" << endl;
        cout << "UID: " << node->UID << " In: " << node->in << " access " << node->access << endl;
    }
}

//=== Verification method ===
bool Node::verifyNodeParameter(Circle& circle, unsigned int sizePopulation, 
                               ID identifier, const vector<Node*>& nodeGroup){
    // Check validity of argument
    if (identifier == no_link) {
        cout<< error::reserved_uid(); 
        return false;
    }
    if (sizePopulation < min_capacity){
        cout<< error:: too_little_capacity(sizePopulation);
        return false;
    }
    if (sizePopulation > max_capacity){
        cout<<error:: too_much_capacity(sizePopulation);
        return false;
    }
    for (auto& node:nodeGroup){
        if(node->UID == identifier){
            cout<<error::identical_uid(identifier);
            return false;
        }
        if(tools::overlapBetweenCircles(circle, node->nodeCircle, dist_min)){
           cout<< error::node_node_superposition(identifier,node->UID);
            return false;
        }
    } 
    nodeCircle = circle;
    nbp = sizePopulation;
    UID = identifier;

    //Dijksra attribut initialisation
    in = true;
    access = infinite_time;
    parent = nullptr;

    return true;
}
bool Node::checkCollisionNodeLink(Node* pNode1,Node* pNode2) const{
    Segment currentSegment = {pNode1->nodeCircle.center, pNode2->nodeCircle.center};
    if (UID != pNode1->UID
        and UID != pNode2->UID
        and tools::overlapBetweenCircleSegment(nodeCircle,currentSegment, 
                                                dist_min)){
            cout << error::node_link_superposition(UID);
            return false;
        }
    return true;
}
bool Node::checkIfNodeIsAlreadyLinked(Node* nodeToCheck) const{
    for (size_t i(0); i < links.size(); ++i){
        if (links[i]->UID == nodeToCheck->UID){
            cout << error::multiple_same_link(UID,nodeToCheck->UID);
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
        cout << error::max_link(UID);
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
    double diameter( nodeCircle.radius*2 );
    double rectangleWidth(diameter*ratioRectangleWidth);
    double rectangleHeight(diameter*ratioRectangleHeight);
    Point topLeftCorner {nodeCircle.center.x - rectangleWidth/2. ,
                         nodeCircle.center.y + rectangleHeight/2. };
    Point topRightCorner {nodeCircle.center.x + rectangleWidth/2.,
                          nodeCircle.center.y + rectangleHeight/2. };
    Point bottomLeftCorner {nodeCircle.center.x - rectangleWidth/2.,
                            nodeCircle.center.y - rectangleHeight/2. };
    Point bottomRightCorner {nodeCircle.center.x + rectangleWidth/2.,
                          nodeCircle.center.y - rectangleHeight/2. };
    tools::drawSegment(Segment{topLeftCorner,topRightCorner});
    tools::drawSegment(Segment{topRightCorner,bottomRightCorner});
    tools::drawSegment(Segment{bottomRightCorner,bottomLeftCorner});
    tools::drawSegment(Segment{bottomLeftCorner,topLeftCorner});
}
Type NodeProduction::getType() const {
    return PRODUCTION;
}
