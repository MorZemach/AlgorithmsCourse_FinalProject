#pragma once
#include "Vertex.h"
#include <string.h>

using namespace std;

struct ArrayNode
{
	int Degree;
	bool Visited;
};

class Graph
{
private:
	int m_NumberOfVertices;
	Vertex* m_VerticesArray;
	ArrayNode* DegreesArray;
	int m_StartVertex;
	int m_EndVertex;

public:
	Graph() {}
	Graph(int i_NumberOfVertices, int i_StartVertex = 0, int i_EndVertex = 0);
	~Graph();

	AdjList* GetAdjList(int i_VerticeX);
	ArrayNode* BFS(int i_StartingPoint);
	ArrayNode* InitVisitArray();
	Graph* Transpose();

	void RemoveEdge(int i_VerticeX, int i_VerticeY);
	void MakeEmptyGraph(int i_NumberOfVertices);
	void AddEdge(int i_VertexX, int i_VertexY);
	void PrintVertex(int i_VertexNumber);
	void DeleteUnnecessaryVertices();
	void DeleteUnnecessaryEdges();
	void PrintGraph();
	void PrintEdges();
	
	//void ReadGraph(string str);
	void ReadGraph(char* i_FileName);
	void InitFileGraph(int i_NumberOfVertices, int i_OriginalVertex, int i_DestinationVertex);

	int AddEdge(int i_VerticeX, int i_VerticeY, int i_WeightEdge);
	bool IsAdjacent(int i_VerticeX, int i_VerticeY);
	int GetStartPoint() { return m_StartVertex; }
	int GetEndPoint() { return m_EndVertex; }
	int isEmpty();

	static Graph* Init();
};



