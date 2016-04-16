/*
 * Map.cpp
 *
 *  Created on: April 16, 2016
 *      Author: Eylam Milner 311212419
 *      		Lucas Aids	 324392992
 */

#include "Map.h"
#include "lodepng.h"
#include <iostream>

// Map's constructor
Map::Map(double mapResolution, double robotSize)
{
	// Initialize robot size
	this->robotSize = robotSize;

	// Initialize map resolution
	this->mapResolution = mapResolution;

	// Initialize map's highest and width
	this->height = 0;
	this->width  = 0;
}

// Loading map
void Map::loadMap(const char* mapFile)
{
	// Decode map file
	lodepng::decode(pixels, width, height, mapFile);

	// Resize the map vector with the height
	map.resize(height);

	// Going over all of the cells in the map
	for (unsigned int i = 0; i < height; i++)
	{
		// Resizing every cell with the given width
		map[i].resize(width);
	}

	// Going over all of the cells to the height of the map
	for (unsigned int i = 0; i < height; i++)
	{
		// Going over all of the cell to the width of the map
		for (unsigned int j = 0; j < width; j++)
		{
			// Checking if the current cell is occupied
			map[i][j] = checkIfCellIsOccupied(i, j);
		}
	}

	// Print the new map
	printMap();
}

// Saving the new map file
void Map::saveMap(const char* mapFile)
{
	// Resizing the map
	inflotedPixels.resize(width * height * 4);

	// Going over all of the cells to the height of the map
	for (unsigned int i = 0; i < height; i++)
	{
		// Going over all of the cells to the width of the map
		for (unsigned int j = 0; j < width; j++)
		{
			// Set the current cell occupation
			setInflotedCellIsOccupied(i, j);
		}
	}

	// Encode map file
	lodepng::encode(mapFile, inflotedPixels, width, height);
}

// Inflating the map's obstacles
void Map::inflateObstacles()
{
	// Initialize robot size in pixels
	int robotSizeInPixels = robotSize / mapResolution;

	// Initialize the radius to inflate
	int inflationRadius = 0.5 * robotSizeInPixels;

	// Resizing inflated map
	inflotedMap.resize(height);

	// Going over the map cells
	for (unsigned int i = 0; i < height; i++)
	{
		// Resizing the each cell's width
		inflotedMap[i].resize(width);
	}

	// Going over the map cells
	for (unsigned int i = 0; i < height; i++)
	{
		// Going over the map cells
		for (unsigned int j = 0; j < width; j++)
		{
			// If current cell is occupied
			if (map[i][j])
			{
				// TODO: Why?
				for (int k = -1 * inflationRadius; k <= inflationRadius; k++)
				{
					// TODO: Why?
					for (int m = -1 * inflationRadius; m <= inflationRadius; m++)
					{
						// TODO: Why?
						if (i + k > 0 && i + k < height && j + m > 0 && j + m < width)
						{
							// Mark cell as occupied in inflated map
							inflotedMap[i + k][j + m] = true;
						}
					}
				}
			}
		}
	}

	// Print the new inflated map
	printInflotedMap();
}

// Checking if a specific cell is occupied
bool Map::checkIfCellIsOccupied(int i, int j)
{
	// Initializing cell variables
	int c = (i * width + j) * 4;
	int r = pixels[c];
	int g = pixels[c + 1];
	int b = pixels[c + 2];

	// If cell is occupied
	if (r == 0 && g == 0 && b == 0)
	{
		// return true value to the map
		return true;
	}

	// if the cell is not occupied, return false value to the map
	return false;
}

// Check if a cell in the inflated map is occupied
void Map::setInflotedCellIsOccupied(int i, int j)
{
	// Initialize color and cell
	int c = (i * width + j) * 4;
	int color = (inflotedMap[i][j] ? 0 : 255);

	// Set the inflated cell color
	inflotedPixels[c] = color;
	inflotedPixels[c + 1] = color;
	inflotedPixels[c + 2] = color;
	inflotedPixels[c + 3] = 255;
}

// Print the give map
void Map::printMap() const
{
	// Going over all of the cells to the height of the map
 	for (unsigned int i = 0; i < height; i++)
	{
 		// Going over all of the cells to the width of the map
		for (unsigned int j = 0; j < width; j++)
		{
			// Print map with occupied or unoccupied cells
			cout << (map[i][j] ? "*" : " ");
		}

		// Go down one line
		cout << endl;
	}
}

// Print the new inflated map
void Map::printInflotedMap() const {

	// Going over all of the cells to the height of the map
	for (unsigned int i = 0; i < height; i++)
	{
 		// Going over all of the cells to the width of the map
		for (unsigned int j = 0; j < width; j++)
		{
			// Print map with occupied or unoccupied cells
			cout << (inflotedMap[i][j] ? "*" : " ");
		}

		// Go down one line
		cout << endl;
	}
}

Map::~Map()
{
	// Notifying map vector is being released
	cout << "Map is being deleted" << endl;

	// Going over all of the cells to the height of the map
	for (unsigned int i = 0; i < height; i++)
	{
		// Going over all of the cells to the width of the map
		for (unsigned int j = 0; j < width; j++)
		{
			// Print map with occupied or unoccupied cells
			// delete map[i][j];
		}
	}
}

