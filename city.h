// Module City (interface)
// made by Vincent GHEROLD and Emile CAILLOL
// version 1.0

#ifndef CITY_H
#define CITY_H

#include <vector>
#include <string>
#include <array>

#include "node.h"

class City {
public:
	static bool readFile(std::string data);
	static void updateDraw();
	static bool save(std::string nom);
	static void emptyNodeGroup();

	static std::string criteriaENJ();
	static std::string criteriaCI();
	static std::string criteriaMTA();

private:
	bool addNode(std::string line,int type);
	bool addLink(std::string line);
	bool initialiseDijkstra();
	void sort();
	double dijkstra(int d, Type type);
	std::string convertDoubleToString(const double& value);
	Node* pickNodeByUID(ID UID) const;
	void showNodeGroup() const;
	std::vector<Node*> getType(Type type);

	std::vector<std::array<Node*,2>> getLinkGroup();

	std::vector<Node*> nodeGroup;
};

#endif
