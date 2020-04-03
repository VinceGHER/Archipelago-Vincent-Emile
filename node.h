// Module Node (interface)
// made by Vincent GHEROLD and Emile CAILLOL
// version 1.0  

#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>


#include "tools.h"
enum Type {HOUSING,TRANSPORT,PRODUCTION,LINK};

class Node;
class NodeHousing;
class NodeTransport;
class NodeProduction;

class Node {
public:
    static void showNodeGroup();
    static Node* pickNodeByUID(ID UID);
    static void emptyNodeGroup();
    static bool addNode(Circle circle, unsigned int sizePopulation, int type, 
                        ID identifier);
    static bool readLine(std::string line,int type);
    static bool addLink(ID UID1, ID UID2);

    ID getUID() const;
    bool createLinkNode(Node& other, const std::vector<Node>& nodeGroup);
    Node(Circle& circle, unsigned int sizePopulation, ID identifier, 
            bool& success);
    virtual void showNode() const;
    virtual ~Node(){}
protected:

    bool checkIfNodeIsAlreadyLinked(Node nodeToCheck) const;
    virtual bool checkLinksLimit() const;

    Circle nodeCircle;
    unsigned int nbp;
    int type;
    ID UID;
    std::vector<ID> links;

};
class NodeHousing: public Node {
public:
    NodeHousing(Circle& circle, unsigned int sizePopulation, ID identifier, 
                bool& success);
    virtual void showNode() const override;
    virtual ~NodeHousing(){}
    virtual bool checkLinksLimit() const override;
};

class NodeTransport: public Node {
public:
    NodeTransport(Circle& circle, unsigned int sizePopulation, ID identifier, 
                  bool& success);
    virtual void showNode() const override;
    virtual ~NodeTransport(){}
    virtual bool checkLinksLimit() const override;
};

class NodeProduction: public Node {
public:
    NodeProduction(Circle& circle, unsigned int sizePopulation, ID identifier, 
                  bool& success);
    virtual void showNode() const override;
    virtual ~NodeProduction(){}
    virtual bool checkLinksLimit() const override;

};
   
#endif