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
	City();
	static bool readFile(std::string data);
	static bool save(std::string nom);
	static void updateDraw(bool shortestPath);
	static void emptyNodeGroup();
	static bool addNodeBridge(double x, double y, Type type);
	static bool editLink(double posX, double posY);
	static bool testEditLink();
	static bool testSelectNode(double x, double y, Type type);
	
	//criteria
	static std::string criteriaENJ();
	static std::string criteriaCI();
	static std::string criteriaMTA();

private:
	//node gestion
	bool addNode(std::string line,int type);
	bool addLink(std::string line);
	void deleteNodeSelected();
	void showNodeGroup() const;
	ID findNewUID();

	//Dijkstra function
	double dijkstra(ID startNodeID, Type type, bool showPath);

	//tools functions
	Node* pickNodeByUID(ID UID) const;
	std::vector<Node*> getType(Type type) const;
	std::vector<std::array<Node*,2>> getLinkGroup() const;

	//attributes
	std::vector<Node*> nodeGroup;
	Node* selectedNode;
};

#endif
