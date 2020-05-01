// Module City (interface)
// Made by Vincent GHEROLD and Emile CAILLOL
// Version 2.0
// Architecture b1

#ifndef CITY_H
#define CITY_H

#include <vector>
#include <string>
#include <array>

#include "node.h"

class City {
public:
	//node gestion
	static bool readFile(std::string data);
	static bool save(std::string nom);
	static void updateDraw();
	static void emptyNodeGroup();
	
	//criteria
	static std::string criteriaENJ();
	static std::string criteriaCI();
	static std::string criteriaMTA();

private:
	//node gestion
	bool addNode(std::string line,int type);
	bool addLink(std::string line);
	void showNodeGroup() const;

	//Dijkstra function
	double dijkstra(ID startNodeID, Type type);

	//tools functions
	Node* pickNodeByUID(ID UID) const;
	std::vector<Node*> getType(Type type) const;
	std::vector<std::array<Node*,2>> getLinkGroup() const;
	std::string convertDoubleToString(const double& value);

	//attributes
	std::vector<Node*> nodeGroup;
};

#endif
