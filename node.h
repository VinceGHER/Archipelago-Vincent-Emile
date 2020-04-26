// Module Node (interface)
// made by Vincent GHEROLD and Emile CAILLOL
// version 1.0  

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
    virtual ~Node(){}

    static bool readLink(std::string line,ID& UID1,ID& UID2);
    bool addLink(Node* nodeToLink);

    virtual bool checkLinksLimit() const = 0;
    virtual void showNode() const;
    
    double dist(Node* node);
    
    //Setter
    void setIn(bool value);
    void setAccess(double value);
    void setParent(double value);

    //Getter
    const ID getUID() const;  
    virtual Type getType() const = 0;
    double getNbp() const;

    //save functions
    std::ostream& saveNode(std::ostream& fichier) const;
    void getVectorLink(std::vector<std::array<Node*,2>>& linkCreated,
                        Node* thisNodePtr) const;
    
    //draw functions
    virtual void drawNode() const;
    void drawLink(std::vector<ID>& linkCreated);

    //verification function
    bool verifyNodeParameter(Circle& circle, unsigned int sizePopulation, 
                             ID identifier,const std::vector<Node*>& nodeGroup);
    bool checkCollisionNodeLink(Node* pNode1,Node* pNode2) const;
    bool checkIfNodeIsAlreadyLinked(Node* nodeToCheck) const;

    
protected:
    Circle nodeCircle;
    unsigned int nbp;
    ID UID;
    std::vector<Node*> links;
    bool in;
    double access;
    double parent;

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
