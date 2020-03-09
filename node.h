// Module Node (interface)
// made by Vincent GHEROLD and Emile CAILLOL
// version 1.0  

#ifndef NODE_H
#define NODE_H
    #include "tools.h"
    #include <vector>
    #include <string>

    enum Type {LOGEMENT,TRANSPORT,PRODUCTION,LINK};

    class Node {
        public:
            static bool read(std::string line,Type type);
            static void showNodeGroup();

        private:
            static bool addNode(Circle circle, unsigned int sizePopulation, 
                                Type t, ID identifier);
            Node(Circle& circle, unsigned int sizePopulation, 
                Type t, ID identifier, bool& success);

            static bool addLink(ID UID1, ID UID2);
            bool checkIfNodeIsAlreadyLinked(Node nodeToCheck) const;
            bool checkLinksLimit() const;

            static Node* pickNodeByUID(ID UID);

            Circle nodeCircle;
            unsigned int nbp;
            Type type;
            ID UID;
            std::vector<ID> links;


    };
#endif