/*
 * Graph.h
 *
 *  Created on: Mar 29, 2016
 *      Author: colman
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include "Node.h"
#include "Map.h"
#include "set"

struct point
{
	bool occupied;
	int row;
	int col;
	double fValue;
	double gValue;
	double hValue;
	int cameFromRow;
	int cameFromCol;
};

class Graph {
private:
	double	graphResolutionInCM;
	double	resolutionRelation;
public:
	vector<vector<Node> > nodes;
	void buildGraphFromMap(const Map map);
	Graph(double graphResolutionInCM);
	virtual ~Graph();
	Node getNodeFromCordinates(int x, int y);
	void paintPathOnMap(Map *map, vector<Node> path, int r, int g, int b);
	void paintPathOnMap(Map *map, Node node, int r, int g, int b);
};

#endif /* GRAPH_H_ */
