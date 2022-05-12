#include "Graph.h"
#include "AdjList.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

Graph::Graph(int i_NumberOfVertices, int i_StartVertex, int i_EndVertex)
{
	int Size = i_NumberOfVertices + 1;

	m_NumberOfVertices = i_NumberOfVertices;
	m_VerticesArray = new Vertex[Size];
	m_StartVertex = i_StartVertex;
	m_EndVertex = i_EndVertex;
	DegreesArray = InitVisitArray();
}

Graph::~Graph()
{
}

void Graph::RemoveEdge(int i_VerticeX, int i_VerticeY)
{
	m_VerticesArray[i_VerticeX].getVertexAdjList()->RemoveSpecificNode(i_VerticeY);
}

void Graph::MakeEmptyGraph(int i_NumberOfVertices)
{
	int Size = i_NumberOfVertices + 1;
	m_StartVertex = 0;
	m_EndVertex = 0;
	m_NumberOfVertices = i_NumberOfVertices;
	m_VerticesArray = new Vertex[Size];
}

int Graph::isEmpty()
{
	int graphIsEmpty = 0;

	if (m_NumberOfVertices == 0)
	{
		graphIsEmpty = 1;
	}

	return graphIsEmpty;
}

ArrayNode* Graph::BFS(int i_StartingPoint)
{
	int currentVertice;
	int Size = m_NumberOfVertices + 1;
	int* Parent = new int[Size];
	AdjList Queue;
	Queue.AddNodeToEndOfList(i_StartingPoint);

	for (int i = 1; i < Size; i++)
	{
		Parent[i] = 0;
		DegreesArray[i].Degree = -1;
		DegreesArray[i].Visited = false;
	}
	DegreesArray[i_StartingPoint].Degree = 0;
	DegreesArray[i_StartingPoint].Visited = true;


	while (Queue.AdjListIsEmpty() != true)
	{
		currentVertice = Queue.RemoveNodeFromTheStartOfTheList();
		AdjList::Node* curr = m_VerticesArray[currentVertice].getVertexAdjList()->getHead();

		while (curr != nullptr)
		{
			if (!DegreesArray[curr->m_VertexNumber].Visited)
			{
				DegreesArray[curr->m_VertexNumber].Visited = true;
				DegreesArray[curr->m_VertexNumber].Degree = DegreesArray[currentVertice].Degree + 1;
				Parent[curr->m_VertexNumber] = currentVertice;
				Queue.AddNodeToEndOfList(curr->m_VertexNumber);
			}

			curr = curr->m_NextAdjacent;
		}
	}

	return DegreesArray;
}

Graph* Graph::Transpose()
{
	Graph* graphT = new Graph(m_NumberOfVertices);

	for (int Index = 1; Index <= m_NumberOfVertices; Index++)
	{
		if (m_VerticesArray[Index].IsDeleted() == false)
		{
			AdjList::Node* curr = m_VerticesArray[Index].getVertexAdjList()->getHead();
			int u = Index;

			while (curr != nullptr)
			{
				int v = curr->m_VertexNumber;
				graphT->AddEdge(v, u);
				curr = curr->m_NextAdjacent;
			}
		}
	}

	return graphT;
}


ArrayNode* Graph::InitVisitArray()
{
	int Size = m_NumberOfVertices + 1;
	ArrayNode* DegreesArr = new ArrayNode[Size];
	for (int i = 1; i <= m_NumberOfVertices; i++)
	{
		if (i == m_StartVertex)
			DegreesArr[i].Degree = 0;
		else
			DegreesArr[i].Degree = -1;

		DegreesArr[i].Visited = false;
	}
	return DegreesArr;
}

void Graph::PrintEdges()
{
	for (int Index = 1; Index <= m_NumberOfVertices; Index++)
	{
		if (m_VerticesArray[Index].IsDeleted() == false && m_VerticesArray[Index].getVertexAdjList() != nullptr)
		{
			AdjList::Node* curr = m_VerticesArray[Index].getVertexAdjList()->getHead();
			while (curr != nullptr)
			{
				cout << Index << " " << curr->m_VertexNumber << " ";
				curr = curr->m_NextAdjacent;
			}
		}
	}
}

void Graph::DeleteUnnecessaryVertices()
{
	for (int index = 1; index < 7; index++)
	{
		if (DegreesArray[index].Degree == -1)
		{
			m_VerticesArray[index].DeleteVertex();
		}
	}
}

void Graph::DeleteUnnecessaryEdges()
{
	for (int index = 1; index <= m_NumberOfVertices; index++)
	{
		AdjList::Node* curr = m_VerticesArray[index].getVertexAdjList()->getHead();
		int u = index;

		while (curr != nullptr)
		{
			int v = curr->m_VertexNumber;
			if (DegreesArray[u].Degree + 1 != DegreesArray[v].Degree) 
			{
				RemoveEdge(u, v);
				if (m_VerticesArray[index].getVertexAdjList()->AdjListIsEmpty() == true)
				{
					break;
				}

			}
			curr = curr->m_NextAdjacent;
		}
	}
}

bool Graph::IsAdjacent(int i_VerticeX, int i_VerticeY)
{
	bool isAdjacent = true;

	if (m_VerticesArray[i_VerticeX].findPrevAdjacent(i_VerticeY)->m_NextAdjacent == nullptr)
	{
		isAdjacent = false;
	}

	return isAdjacent;
}

int Graph::AddEdge(int i_VerticeX, int i_VerticeY, int i_WeightEdge)
{
	int edgeAddedSuccessfully = 0;

	if (m_VerticesArray[i_VerticeX].getVertexAdjList()->AddNodeToEndOfList(i_VerticeY, i_WeightEdge) == true)
	{
		edgeAddedSuccessfully = 1;
		m_NumberOfVertices++;
	}

	return edgeAddedSuccessfully;
}

void Graph::AddEdge(int i_VertexX, int i_VertexY)
{
	m_VerticesArray[i_VertexX].getVertexAdjList()->AddNodeToEndOfList(i_VertexY);
}

AdjList* Graph::GetAdjList(int i_VerticeX)
{
	return m_VerticesArray[i_VerticeX].getVertexAdjList();
}

void Graph::PrintGraph()
{
	cout << "Graph G is: " << endl;


	for (int vertexNumber = 1; vertexNumber <= m_NumberOfVertices; vertexNumber++)
	{
		if (m_VerticesArray[vertexNumber].IsDeleted() == false)
		{
			if (m_VerticesArray[vertexNumber].getVertexAdjList()->getHead() != nullptr)
				PrintVertex(vertexNumber);
		}
	}
}

void Graph::PrintVertex(int i_VertexNumber)
{
	AdjList::Node* currentAdj = m_VerticesArray[i_VertexNumber].getVertexAdjList()->getHead();
	
	cout << i_VertexNumber << ": ";

	while (currentAdj ->m_NextAdjacent != nullptr)
	{
		cout << "(" << i_VertexNumber << "," << currentAdj->m_VertexNumber << "), ";
		currentAdj = currentAdj->m_NextAdjacent;
	}

	cout << "(" << i_VertexNumber << "," << currentAdj->m_VertexNumber << ")" << endl;
}

//void Graph::ReadGraph(string str)
void Graph::ReadGraph(char* i_FileName)
{
	ifstream graphFile;
	int numberOfVertices, origin, destination, verticeX, verticeY;

	//graphFile.open(str);
	graphFile.open(i_FileName);
	if (!graphFile)
	{
		cout << "Error with infile!" << endl;
		exit(-1);
	}

	graphFile >> numberOfVertices;
	graphFile >> origin;
	graphFile >> destination;

	InitFileGraph(numberOfVertices, origin, destination);

	while (!graphFile.eof())
	{
		graphFile >> verticeX;
		graphFile >> verticeY;
		this->AddEdge(verticeX, verticeY);
	}

	graphFile.close();
}

//void Graph::ReadGraph()
//{
//	ifstream graphFile;
//	int numberOfVertices, origin, destination, verticeX, verticeY;
//
//	graphFile.open("graphFile.txt");
//	if (!graphFile)
//	{
//		cout << "Error with infile!" << endl;
//		exit(-1);
//	}
//
//	graphFile >> numberOfVertices;
//	graphFile >> origin;
//	graphFile >> destination;
//	
//	this->InitFileGraph(numberOfVertices, origin, destination);
//
//	while (!graphFile.eof())
//	{
//		graphFile >> verticeX;
//		graphFile >> verticeY;
//		this->AddEdge(verticeX, verticeY);
//	}
//
//	graphFile.close();
//}

void Graph::InitFileGraph(int i_NumberOfVertices, int i_OriginalVertex, int i_DestinationVertex)
{
	this->m_NumberOfVertices = i_NumberOfVertices;
	this->m_StartVertex = i_OriginalVertex;
	this->m_EndVertex = i_DestinationVertex;
	this->m_VerticesArray = new Vertex[i_NumberOfVertices + 1];
	this->DegreesArray = InitVisitArray();
}

Graph* Graph::Init()
{
	int Vertices, Origin, Destination, VerticeX, VerticeY;

	//cout << "Please Enter the number of Vertices at your graph: ";
	cin >> Vertices;
	//cout << "Enter the number of your starting point and Destination point Vertices: ";
	cin >> Origin >> Destination;

	if (Vertices < 0 || Destination > Vertices || Origin < 0)
	{
		cout << "Invalid Input.";
		exit(1);
	}

	Graph graph(Vertices, Origin, Destination);
	while (cin.peek() != '\n')
	{
		cin >> VerticeX;
		cin >> VerticeY;
		graph.AddEdge(VerticeX, VerticeY);
	}

	return &graph;
}




