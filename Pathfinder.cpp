#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "Pathfinder.h"
using namespace std;

Pathfinder::Pathfinder() {
	srand(time(NULL));
    for(int i =0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 5; k++){
                maze[i][j][k] = 1;
            }
        }
    }
}

string Pathfinder::toString() const 
	{
		stringstream stream;
		for(int i=0;i<5;i++)
		{
			for(int j=0;j<5;j++)
			{
				for (int k=0;k<5;k++)
				{
					if(k<4)
					stream << maze[i][j][k] <<" ";
					else if(k=4)
					stream << maze[i][j][k];
				}
				stream << endl;
			}
			if(i<4)
			{
			stream << endl;
			}
		}
		string out = stream.str();
		return out;
		
	}
	

	void Pathfinder::createRandomMaze()
	{
		for(int i=0;i<5;i++)
		{
			for(int j=0;j<5;j++)
			{
				for (int k=0;k<5;k++)
				{
					maze [i][j][k]=rand()%2;
				}
			}
		}
		maze[0][0][0]=1;
		maze[4][4][4]=1;
	}
	
	bool Pathfinder::importMaze(string file_name)
	{
		ifstream infile(file_name.c_str());
		char num;
		int count = 0;
		if(infile.is_open())
		{
			while(infile >> num)
			{
					if(num == '1')
					{
						count++;
					}
					else if(num == '0')
					{
						count++;
					}
					else 
					{
						cout << "fail0";
						return false;
					}
			}
		infile.close();
		}
		else 
		{ 
			cout << "fail1";
			return false;
		}
		if(count != 125)
		{
			cout << "fail2";
			return false;
		}
		

		infile.open(file_name);
		int temp [5][5][5];
		if(infile.is_open())
		{
			string row;
			int number;
			for(int i=0;i<5;i++)
			{
				for(int j=0;j<5;j++)
				{
					getline(infile,row);
					stringstream stream(row);

					for (int k=0;k<5;k++)
					{
						stream >> number;
						if(k ==0 && j== 0 && i ==0)
						{
							if(number == 0)
							{
								cout << "fail3";
								return false;
							}
							
						}
						else if(k == 4 && j== 4 && i == 4)
							{
								if(number == 0)
								{
									cout << "fail4";
									return false;
								}
							}
						temp[i][j][k]=number;
					}
				}
				getline(infile,row);
			}	
			infile.close();
		}
		for(int i=0;i<5;i++)
		{
			for(int j=0;j<5;j++)
			{
				for (int k=0;k<5;k++)
				{
					maze [i][j][k]=temp[i][j][k];
					cout << maze[i][j][k];
				}
			}
		}
		return true;
	}

	void Pathfinder::checkMaze()
	{
		for(int i=0;i<5;i++)
		{
			for(int j=0;j<5;j++)
			{
				for (int k=0;k<5;k++)
				{
					if(maze [i][j][k]!=0 && maze [i][j][k]!=1)
					maze [i][j][k]=1;
				}
			}
		}
	}
	vector<string> Pathfinder::solveMaze()
	{
		findPath(maze,0,0,0);
		checkMaze();
		for(auto s:solution) 
		{
		cout <<s<<endl;
	    }
	    return solution;
	}
	

	bool Pathfinder::findPath(int a[5][5][5], int x, int y, int z)
	{
  	vector<string> solution;
	  if (x < 0 || y < 0 || y < z|| x >= 5 || y >= 5 || z >= 5)
	    return false;   

	  else if (a[x][y][z]!= 1)
	    return false;

	  else if (x == 5 - 1 && y == 5 - 1 && z == 5-1) 
		{
	    a[x][y][z] = 3;
	    solution.push_back("("+to_string(x)+","+to_string(y)+","+to_string(z)+")");
	    return true;
	  }
	  else { 
	    a[x][y][z] = 3;
	    if (findPath(a, x-1, y, z) // forward
	        || findPath(a, x+1, y, z) // backward
	        || findPath(a, x, y-1, z) // Left
	        || findPath(a, x, y+1, z ) // right
					||findPath(a, x, y, z-1 ) //up
					||findPath(a, x, y, z+1 )) { //down
	      solution.push_back("("+to_string(x)+","+to_string(y)+","+to_string(z)+")");
	      return true;
	    }
	    else {
	      a[x][y][z] = 2;  // Dead end.
	      return false;
	    }
	  }
	}
		
