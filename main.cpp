//seprod5a
//File: Main file for maze problem
//Reads in a maze and solves the maze
#include <iostream>
#include <fstream>
#include "maze.h"


using namespace std;

int main()
{
        ifstream fin;
        
        // Read the maze from the file.
        string fileName;
        cout << "Input filepath" << endl;
        cin >> fileName;
        
        fin.open(fileName.c_str());
        if (!fin)
        {
                cerr << "Cannot open " << fileName << endl;
                exit(1);
        }
        
        try
        {
                
                graph g;
                while (fin && fin.peek() != 'Z')
                {
                        maze m(fin);
                        m.mapMazeToGraph(g);
                        cout << "------------------------------------------------------" << endl;
                        cout << "               Finding path recursively" << endl;
                        m.initializePathRecursive(0, 0, g);
                        if (m.Found())
                        {
                                m.printPathRecursive(0, 0);
                        }
                        else
                                cout << "No path was found" << endl;
                        cout << "------------------------------------------------------" << endl;
                        cout << "             Finding path non-recursively" << endl;
                        m.findPathNonRecursive(0, 0, g);
                }
                
                
        } 
        catch (indexRangeError &ex) 
        { 
                cout << ex.what() << endl; exit(1);
        }
        catch (rangeError &ex)
        {
                cout << ex.what() << endl; exit(1);
        }
        
}