/*
 * Main.cpp
 *
 *  Created on: April 16, 2016
 *      Author: Eylam Milner 311212419
 *      		Lucas Aids	 324392992
 */

#include "Map.h"
#include "Graph.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "AStarAlgorithm.h"

using namespace std;

int main()
{
	// Parameters from parameters file
	string	mapFile;
	cordinates robotStartCord;
	double 	robotStartYAW;
	cordinates goalCord;
	double 	robotHeight;
	double 	robotWidth;
	double 	mapResolutionCM;
	double 	gridResolutionCM;

	// Open parameters file
	ifstream parameters;
	parameters.open("parameters.txt");

	if (parameters.is_open())
	{
		string line;
		string lineName;

		// Get Map File - line contains map: path
		getline(parameters,line);
		std::istringstream mapLine(line);
		mapLine >> lineName >> mapFile;

		// Get Robot starting position - line contains startLocation: x y yaw
		getline(parameters,line);
		istringstream startLocationLine(line);
		startLocationLine >> lineName >> robotStartCord.x >> robotStartCord.y >> robotStartYAW;

		// Get Goal - line contains goal: x y
		getline(parameters,line);
		istringstream goalLine(line);
		goalLine >> lineName >> goalCord.x >> goalCord.y;

		// Get Robot Size - line contains robotSize: height width
		getline(parameters,line);
		istringstream sizeLine(line);
		sizeLine >> lineName >> robotHeight >> robotWidth;

		// Get Map resolution in CM - line contains MapResolutionCM: resolution
		getline(parameters,line);
		istringstream mapResolutionLine(line);
		mapResolutionLine >> lineName >> mapResolutionCM;

		// Get Grid resolution in CM - line contains GridResolutionCM: resolution
		getline(parameters,line);
		istringstream gridResolutionLine(line);
		gridResolutionLine >> lineName >> gridResolutionCM;

		parameters.close();
	}
	else
	{
		cout << "Unable to open file";
		return 0;
	}

	// Creating a map object with the given parameters
	Map map(mapResolutionCM, robotHeight, robotWidth);

	// Loading map
	map.loadMap(mapFile);

	// Inflate all of the obstacles in the give map
	map.inflateObstacles();

	// Create a graph from map to run the a star algorithm on it
	Graph graph(gridResolutionCM);
	graph.buildGraphFromMap(map);

	Point start = graph.getPointFromCordinates(robotStartCord);
	Point goal = graph.getPointFromCordinates(goalCord);
	AStarAlgorithm algo(graph.nodes, start, goal);
	vector<Point> path = algo.StartAlgorithm();
	graph.paintPathOnMap(&map, path,255,0,0);
	//graph.paintPathOnMap(&map, start,255,0,0);
	//graph.paintPathOnMap(&map, goal,0,0,255);
	// Save the new inflated map the a new file
	map.saveMap("infloatedMap.png");

	// Return value
	return 0;
}
