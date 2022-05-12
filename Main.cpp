using namespace std;
#include <iostream>
#include <string>
#include <stdlib.h>
#include "Graph.h"


int main()
{
	Graph fileGraph;
	fileGraph.ReadGraph((char*)"test_data6.txt");
	fileGraph.PrintGraph();

    Graph G = *(Graph::Init());
	ArrayNode* DArr = G.BFS(G.GetStartPoint());
	G.DeleteUnnecessaryEdges();
	Graph* GT = G.Transpose();
	ArrayNode* DArr2 = GT->BFS(G.GetEndPoint());
	GT->DeleteUnnecessaryVertices();
	Graph* H=GT->Transpose();
	H->PrintEdges();


	//6 1 3 6 5 5 6 6 1 1 6 1 5 2 5 1 2 2 1 5 4 4 2 5 3 4 3 2 3 3 1
}