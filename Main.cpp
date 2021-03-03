#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Graph {
private:
   bool** adj_matrix;
   int max_size;
   int current_size;
public:
   Graph();
   Graph(int);
   bool isEmpty();
   void createGraph(std::string);
   void DFSRecurse(int, bool*&);
   bool isConnected();
};

Graph::Graph() { //default constructor
   max_size = 10;
   adj_matrix = new bool*[10]; //10 rows
   for(int i = 0; i < 10; i++) { //for each row
      adj_matrix[i] = new bool[10]; //create the row of size 10
      for(int j = 0; j < 10; j++) { //for each entry in the row
         adj_matrix[i][j] = false; //note the absence of an edge
      }
   }
}

Graph::Graph(int n) { //overloaded constructor -- create an n x n adj_matrix
   max_size = n;
   adj_matrix = new bool*[n]; //n rows
   for(int i = 0; i < n; i++) { //for each row
      adj_matrix[i] = new bool[n]; //create the row of size n
      for(int j = 0; j < n; j++) { //for each entry in the row
         adj_matrix[i][j] = false; //note the absence of an edge
      }
   }
}

bool Graph::isEmpty() {
   return current_size == 0;
}

void Graph::createGraph(std::string filename) {
   std::ifstream ifs(filename); //read in the graph file
   std::string line = "";
   getline(ifs, line); //get first line
   current_size = stoi(line); //store the number of vertices in the first line as the current_size
   while(getline(ifs, line)) {
      //read in first number
      //for each subsequent number
      //mark adj_matrix[first number][current_number] = true;
      int start_vertex = stoi(line.substr(0,1)); //read first number in the line as the current starting vertex
      for(unsigned int i = 2; i < line.size(); i++) { //the third index of <line> will be the first vertex to connect
         if(i % 2 == 0) { //at even indices will be the vertices to connect. At odd indices will be spaces, so ignore those
            adj_matrix[start_vertex - 1][stoi(line.substr(i, 1)) - 1] = true; //convert the current end vertex to an int, then normalize both vertices for 0-based indexing. Mark that there is an edge between the two vertices
         }
      }
   }
}

void Graph::DFSRecurse(int vertex, bool*& visited) { //Recursive DFS Search Algorithm. reference to the pointer because we want to directly modify the visited array
   if(!visited[vertex]) { //if vertex has not been visited
      visited[vertex] = true; //mark the vertex as visited
      for(int j = 0; j < current_size; j++) { //for each vertex in vertex's row
         if(adj_matrix[vertex][j]) { //if vertex connects to the jth vertex
            DFSRecurse(j, visited); //visit the jth vertex
         }
      }
   }
}

bool Graph::isConnected() { //returns whether the graph is strongly connected
   bool is_connected = true;
   bool* visited = new bool[current_size]; //visited array

   for(int i = 0; i < current_size; i++) { //for each vertex
      for(int j = 0; j < current_size; j++) { //initialize every value in the visited array to be false
         visited[j] = false;
      }

      DFSRecurse(i, visited); //perform a DFS on the ith vertex

      for(int j = 0; j < current_size; j++) { //for each value in visited array
         if(!visited[j]) { //if the jth vertex has not been visited
            is_connected = false; //we know the graph is not connected
            break; //so stop searching for unvisited nodes
         }
      }

      if(!is_connected) { //if we already know the graph is not connected,
         break; //don't loop around to do any more DFS
      }
   }

   return is_connected;
}

using namespace std;

int numLines(string filename) {
   ifstream ifs(filename);
   string line = "";
   getline(ifs, line);
   return stoi(line);
}

int main()
{
   cout << "Graph Filename: ";
   string filename = "";
   cin >> filename;
   cout << endl;

   int graph_size = numLines(filename);
   Graph user_graph(graph_size);
   user_graph.createGraph(filename);

   if(user_graph.isConnected()) {
      cout << "connected" << endl;
   }
   else {
      cout << "not connected" << endl;
   }

   return 0;
}
