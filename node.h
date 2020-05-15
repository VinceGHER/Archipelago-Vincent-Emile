// Module Node (interface)
// Made by Vincent GHEROLD and Emile CAILLOL
// Version 2.1
// Architecture b1

#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>
#include <iostream>
#include <array>

#include "tools.h"

enum Type {HOUSING,TRANSPORT,PRODUCTION,LINK};

class Node;
class NodeHousing;
class NodeTransport;
class NodeProduction;

class Node {
public:

    Node(std::string line,int type,bool& success,const std::vector<Node*>& nodeGroup);
    virtual ~Node(){};

    static bool readLink(std::string line,ID& UID1,ID& UID2);
    bool addLink(Node* nodeToLink);
    void deleteLink(Node* node);
    virtual void showNode() const;
    
    double dist(Node* node);  

    static Node* selectNode(double posX, double posY, 
                            const std::vector<Node*>& nodeGroup); 
    
    Node* changeNodeCoordinates(double x, double y, Node* selectedNode);
    
    //getters
    const ID getUID() const;  
    virtual Type getType() const = 0;
    double getNbp() const;
    double getAccess() const;

    //save functions
    std::ostream& saveNode(std::ostream& fichier) const;
    
    //draw functions
    virtual void drawNode() const;
    void drawLink(std::vector<std::array<Node*,2>>& linkCreated,Node* thisNodePtr,
                  bool drawing)const;

    //Dijkstra functions
    static Node* dijkstra(std::vector<Node*>& nodeGroup, Type type);
    void initNodeDijkstra(ID startNode);
    static void sortNodeGroup(std::vector<Node*>& nodeGroup, ID UIDToUpdate);
    static void drawSortestPath(Node* nodeFinish);
    static void showdijkstra(const std::vector<Node*>& nodeGroup);
    
    //verification functions
    bool checkCollisionNodeLink(Node* pNode1,Node* pNode2) const;
    bool checkIfNodeIsAlreadyLinked(Node* nodeToCheck) const;
    virtual bool checkLinksLimit() const = 0;

protected:
    //diastra
    static size_t findMinAccess(const std::vector<Node*>& nodeGroup);
    static double computeAccess(Node* node1, Node* node2);

    //verification functions
    bool verifyNodeParameter(Circle& circle, unsigned int sizePopulation, 
                             ID identifier,const std::vector<Node*>& nodeGroup);

    Circle nodeCircle;
    unsigned int nbp;
    ID UID;
    std::vector<Node*> links;

    //Dijksra attributs
    bool in;
    double access;
    Node* parent;
};
class NodeHousing: public Node {
public:
    NodeHousing(std::string line,int type,bool& success,
                const std::vector<Node*>& nodeGroup);
    virtual ~NodeHousing(){}
    virtual void showNode() const override;
    virtual bool checkLinksLimit() const override;
    virtual void drawNode() const override;
    virtual Type getType() const override;
};

class NodeTransport: public Node {
public:
    NodeTransport(std::string line,int type,bool& success,
                  const std::vector<Node*>& nodeGroup);
    virtual ~NodeTransport(){}
    virtual void showNode() const override;
    virtual bool checkLinksLimit() const override;
    virtual void drawNode() const override;
    virtual Type getType() const override;
};

class NodeProduction: public Node {
public:
    NodeProduction(std::string line,int type,bool& success,
                   const std::vector<Node*>& nodeGroup);
    virtual ~NodeProduction(){}
    virtual void showNode() const override;
    virtual bool checkLinksLimit() const override;
    virtual void drawNode() const override;
    virtual Type getType() const override;

};
   
#endif
