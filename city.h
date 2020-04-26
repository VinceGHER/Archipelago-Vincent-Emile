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
	static bool save(std::string nom);
	static void updateDraw();
	static void emptyNodeGroup();

	static std::string criteriaENJ();
	static std::string criteriaCI();
	static std::string criteriaMTA();

private:
	bool addNode(std::string line,int type);
	bool addLink(std::string line);
	std::string convertDoubleToString(const double& value);
	void showNodeGroup() const;

	//dijkstra Methods
	void initDijkstra(ID startNodeID);
	void sort(int d);
	double dijkstra(ID startNodeID, Type type);
	int findMinAccess();
	double computeAccess(int n,int lv);
	void sortUIDTable(std::vector<ID>& UIDTable,ID UIDToUpdate);


	//Tools Methods
	Node* pickNodeByUID(ID UID) const;
	std::vector<Node*> getType(Type type) const;
	std::vector<std::array<Node*,2>> getLinkGroup() const;

	std::vector<Node*> nodeGroup;
};

#endif
