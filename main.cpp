// Project 5
// seprod5b
//
// File: Main file for maze problem
// Reads in a maze and solves the maze
#include <iostream>
#include <fstream>
#include "maze.h" //include maze class


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
                
                graph g; // create graph
                while (fin && fin.peek() != 'Z')
                {
                        maze m(fin);
                        m.mapMazeToGraph(g); //create graph based on read maze
                        
                        //find shortest path using BFS
                        cout << "------------------------------------------------------" << endl;
                        cout << "               Finding shortest path" << endl;
                        cout << "                Using BFS Algorithm" << endl;
                        bool found = m.findShortestPath1(0, 0, m.getRow() - 1, m.getCol() - 1, g);
                        if (found)
                                m.printPath(0, 0);
                        else
                                cout << "Path not found" << endl;
                        
                        //find shortest path using Dijkstra's Algorithm
                        cout << "------------------------------------------------------" << endl;
                        cout << "               Finding shortest path" << endl;
                        cout << "             Using Dijkstra's Algorithm" << endl;
                        found = m.findShortestPath2(0, 0, m.getRow() - 1, m.getCol() - 1, g);
                        if (found)
                                m.printPath(0, 0);
                        else
                                cout << "Path not found" << endl;
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