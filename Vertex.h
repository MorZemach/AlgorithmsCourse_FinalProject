#pragma once
#include "AdjList.h"

class Vertex
{
private:
	int m_VertexDegree;
	AdjList* m_AdjacentList;

public:
	Vertex();
	~Vertex();
	bool IsDeleted();
	void DeleteVertex() { m_AdjacentList = nullptr; }
	AdjList* GetHead() { return m_AdjacentList; }
	bool setVertexDegree(int i_VertexDegree);
	AdjList* getVertexAdjList();
	void removeEdge(int i_VertexAdjacent);
	AdjList::Node* findPrevAdjacent(int i_VertexNamber);
};

