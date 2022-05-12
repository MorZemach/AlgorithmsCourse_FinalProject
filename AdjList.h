#pragma once
class AdjList
{
public:
	struct Node
	{
		int m_VertexNumber;
		int m_WeightEdge;
		Node* m_NextAdjacent;

		Node(int i_NumberOfVertex = 0, int i_WeightEdge = 0);
		~Node() {}
	};

private:
	Node* m_Head;
	Node* m_Tail;

public:
	AdjList();
	~AdjList();
	AdjList::Node* getHead() { return m_Head; }
	bool AdjListIsEmpty();
	void MakeEmptyList();
	int RemoveFromTail();
	bool AddNodeToEndOfList(int i_NumberOfVertex, int i_WeightEdge = 0);
	int RemoveNodeFromTheStartOfTheList();
	void RemoveSpecificNode(int i_AdjacentVertex);
	Node* findPrevVertexAdjacent(int i_AdjacentVertex);
};

