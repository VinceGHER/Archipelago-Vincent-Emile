// Module Node (interface)
// made by Vincent GHEROLD and Emile CAILLOL
// version 1.0  

#ifndef NODE_H
#define NODE_H
    #include <vector>
    #include <string>

    #include "tools.h"
    enum Type {LOGEMENT,TRANSPORT,PRODUCTION,LINK}; //poser à l'assistant?

    class Node {
    public:
        static bool readLine(std::string line,int type);
        static void showNodeGroup();

    private:
        static bool addNode(Circle circle, unsigned int sizePopulation, 
                            int t, ID identifier);
        Node(Circle& circle, unsigned int sizePopulation, 
            int t, ID identifier, bool& success);

        static bool addLink(ID UID1, ID UID2);
        bool checkIfNodeIsAlreadyLinked(Node nodeToCheck) const;
        bool checkLinksLimit() const;

        static Node* pickNodeByUID(ID UID);

        Circle nodeCircle;
        unsigned int nbp;
        int type;
        ID UID;
        std::vector<ID> links;

    };
#endif