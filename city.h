// Module City (interface)
// made by Vincent GHEROLD and Emile CAILLOL
// version 1.0

#ifndef CITY_H
#define CITY_H

#include <vector>
#include <string>

#include "node.h"

class City {
public:
	static bool readFile(char * data);
	static void updateDraw();
	static bool save(std::string nom);

private:
	bool addNode(std::string line,int type);
	bool addLink(std::string line);
	Node* pickNodeByUID(ID UID) const;
	void showNodeGroup() const;
	void emptyNodeGroup();
	std::vector<Node*> getType(Type type);

	double CriteriaENJ();
	double CriteriaCI();

	std::vector<Node*> nodeGroup;
};

#endif
