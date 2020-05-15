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
	static void updateDraw(bool shortestPath, Node* selectedNode);
	static void emptyNodeGroup();
	static bool addNode(double x, double y, Type type);
	static bool addLink(Node* nodeToLink1, Node* nodeToLink2);
	static void deleteNode(Node* nodeToDelete);
	static void moveNode(Point newPos, Node* nodeToMove);
	static Node* getClickedNode(Point pos, bool& isOnBorder,Node* selectedNode);

	//criteria
	static std::string criteriaENJ();
	static std::string criteriaCI();
	static std::string criteriaMTA();

private:
	//node gestion
	bool addNode(std::string line,int type);
	bool addLink(std::string line);
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
};

#endif
