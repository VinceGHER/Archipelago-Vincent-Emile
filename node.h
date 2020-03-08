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
            static bool addLink(ID UID1, ID UID2);
           
            static bool pickNodeIndex(ID UID, size_t& nIndex);
            Node(Circle circle, unsigned int sizePopulation, 
                Type t, ID identifier);
            bool checkIfNodeIsAlreadyLinked(Node nodeToCheck) const;
            bool checkLinksLimit() const;
            Circle nodeCircle;
            unsigned int nbp;
            Type type;
            ID UID;
            std::vector<unsigned int> links;


    };
#endif