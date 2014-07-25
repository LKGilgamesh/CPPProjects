#include <iostream>
#include <string>
using namespace std;

const int MAX_VERTICES = 100;
const int MAX_EDGES = 4950;


struct Graph{
	string vertices[MAX_VERTICES];
	int edges[MAX_EDGES][2];
	int numVertices;
	int numEdges;
	
	Graph(){
		numVertices = 0;
		numEdges = 0;
	}

	void printGraph(){
		int index = 0;
		cout << "Vertices: ";
		for(int i = 0; i < numVertices; i++){
			cout << "[" << vertices[i] << "] ";
		}
		cout << endl << "Edges: ";
		for(int j = 0; j < numEdges; j++){
			printEdge(j);
		}
		cout << endl;
	}

	void printEdgesOfVertex(string vert){
		int index = findIndex(vert);
		if(index == -1){
			cout << "[" << vert << "] does not exist!"; 	
		}
		else{
			cout << "[" << vert << "]: "; 
			for(int i = 0; i < numEdges;i++){
				for(int j = 0; j < 2; j++){
					if(edges[i][j] == index){
						printEdge(i);
					}
				}
			}
		}
		cout << endl;
	}

	void addVertex(string vert){
		vertices[numVertices] = vert;
		numVertices++;
	}

	void addEdge(string vert1, string vert2){
		int vertex1 = -1;
		int vertex2 = -1;
		vertex1 = findIndex(vert1);
		vertex2 = findIndex(vert2);
		if(vertex1 == -1 || vertex2 == -1){
			cout << "One or both of the vertex names is incorrect!";
		}
		else{
			edges[numEdges][0] = vertex1;
			edges[numEdges][1] = vertex2;
			numEdges++; 
		}
	}
	int findIndex(string name){
		int index = -1;
		for(int i=0;i<numVertices;i++){
			if(name == vertices[i]){
				index = i;
			}
		}
		return index;
	}
	void printEdge(int index){
		cout << "(" << vertices[edges[index][0]] << ", " << vertices[edges[index][1]] << ") ";
	}
};



//use (.) for references and (->) for pointers
//e.g. = something.something2 or something->something3

int main(int argc, char ** argv){
	Graph graph;
	int select = 6;

	while(select != 0){
		cout << endl;
		cout << "0. Exit\n1. Add a vertex\n2. Add an edge\n3. Print the graph\n4. Print edges of a vertex\n" << endl;
		cin >> select;

		if(select == 0){
			cout << "Goodbye." << endl;
		}
		else if(select == 1){
			string name;
			cout << "Vertex name -- ";
			cin >> name;
			graph.addVertex(name);
			
		}
		else if(select == 2){
			string name1, name2;
			cout << "First vertex in edge -- ";
			cin >> name1;
			cout << "\nSecond vertex in edge -- ";
			cin >> name2;
			graph.addEdge(name1,name2);
		
		}
		else if(select == 3){
			graph.printGraph();
		}
		else if(select == 4){
			string name;
			cout << "Vertex name -- ";
			cin >> name;
			graph.printEdgesOfVertex(name);
		}
		else{
			cout << "Not a valid option" << endl;
		}
	}
	return 0;
}


