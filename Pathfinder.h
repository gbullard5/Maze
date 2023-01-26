#ifndef Pathfinder_h
#define Pathfinder_h

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include "PathfinderInterface.h"
using namespace std;

class Pathfinder
{
public:

	Pathfinder();
	
	virtual string toString() const;
	virtual void createRandomMaze();
	virtual bool importMaze(string file_name);
	virtual vector<string> solveMaze();
	bool findPath(int a[5][5][5], int x, int y, int z);
	void checkMaze();
protected:
  
  vector<string> solution;
	int maze [5][5][5];
	
};

#endif