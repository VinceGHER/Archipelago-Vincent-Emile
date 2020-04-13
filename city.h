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

private:
	bool addNode(std::string line,int type);
	bool addLink(std::string line);
	Node* pickNodeByUID(ID UID) const;
	void showNodeGroup() const;
	void emptyNodeGroup();

	double CriteriaENJ();
	double CriteriaCI();

	std::vector<Node*> nodeGroup;
};

#endif
