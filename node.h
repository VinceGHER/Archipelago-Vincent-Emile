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
    class NodeManager;

    class NodeManager {
    public:
        bool readLine(std::string line,int type);
        void showNodeGroup();
    private:
        bool addNode(Circle circle, unsigned int sizePopulation, 
                            int t, ID identifier);
        bool addLink(ID UID1, ID UID2);
        Node* pickNodeByUID(ID UID);
        std::vector<Node> nodeGroup;
    };

    class Node {
    public:
        ID getUID() const;
        bool createLinkNode(Node& other, const std::vector<Node>& nodeGroup);
        Node(Circle& circle, unsigned int sizePopulation, int t, ID identifier, 
             bool& success, const std::vector<Node>& nodeGroup);
        void showNode() const;
    private:
    
        bool checkIfNodeIsAlreadyLinked(Node nodeToCheck) const;
        bool checkLinksLimit() const;

        Circle nodeCircle;
        unsigned int nbp;
        int type;
        ID UID;
        std::vector<ID> links;

    };
   
#endif