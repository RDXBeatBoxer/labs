#pragma once
#include <vector>
#include <iostream>
#include <limits>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <queue>
#include <sstream>
#include <string>
#include <GL/glut.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int CIRCLE_RADIUS = 20;
const int TEXT_OFFSET_X = 6;
const int TEXT_OFFSET_Y = 5;
#ifndef M_PI
#define M_PI 3.14
#endif

template<typename T>
struct Vertex {
	sf::CircleShape shape;
	T value;
	sf::Text text;
};

template<typename T>
struct Edge {
	sf::Vertex line[2];
	sf::Text text;
};

template<typename T>
class Graph
{
public:
	Graph() {}
	Graph(const int& size);
	~Graph(){}
	void insertEdge(const T& vert_1, const T& vert_2, int weight); 
	void insertVertex(const T& vert);
	void deleteVertex(){ this->vertList.pop_back(); }
	int getAmountEdges();
	int getAmountVertexes() { return this->vertexV.size(); }
	bool isFull() { return this->vertexV.size() == this->maxSize; }
	bool isEmpty() { return this->vertexV.size() == 0; }
	int getVertexPos(const T& vert);
	int getWeight(const T& vert_1, const T& vert_2);
	std::vector<T> getNbrs(const T& vert);
	void print();
	void dijkstra(const Graph<T>& graph, const T& source);
	void DFS(T& startVertex, bool* visitedVertes);
	void BFS(T& startVertex, bool* visitedVertes);
	void visualizeGraph();
private:
	std::vector<T> vertexV;
	std::vector<std::vector<int>> adjMatrix;
	int maxSize;
	bool isAddingVertex = false; 
	bool isAddingEdge = false; 
	T selectedVertex; 
	std::queue<T> VertexQ;
};

template<typename T>
Graph<T>::Graph(const int& size)
{
	this->maxSize = size;
	this->adjMatrix = std::vector<std::vector<T>>(size, std::vector<T>(size));

	for (int i = 0; i < this->maxSize; i++)
	{
		for (int j = 0; j < this->maxSize; j++)
			this->adjMatrix[i][j] = 0;
	}
}

template<typename T>
void Graph<T>::insertEdge(const T & vert_1, const T & vert_2, int weight)
{
	if (getVertexPos(vert_1) != -1 && this->getVertexPos(vert_2) != -1)
	{
		int vertPos_1 = getVertexPos(vert_1);
		int vertPos_2 = getVertexPos(vert_2);

		if (this->adjMatrix[vertPos_1][vertPos_2] != 0
		&& this->adjMatrix[vertPos_2][vertPos_1] != 0)
		{
			std::cout << "The Edge between verts already exist" << std::endl;
			return;
		}
		else
		{
			adjMatrix[vertPos_1][vertPos_2] = weight;
			adjMatrix[vertPos_2][vertPos_1] = weight;
		}
	}
	else
	{
		std::cout << "Two(or one of them) verts doesnt exist in graph" << std::endl;
		return;
	}
}

template<typename T>
void Graph<T>::insertVertex(const T& vert)
{
	if (this->isFull())
	{
		std::cout << "Cant add vert" << std::endl;
		return;
	}
	this->vertexV.push_back(vert);
}

template<typename T>
int Graph<T>::getAmountEdges()
{
	int amount = 0;
	if (!this->isEmpty())
	{
		for (int i = 0; i < this->vertexV.size(); i++)
		{
			for (int j = 0; j < this->vertexV.size(); j++)
				if (this->adjMatrix[i][j] != 0) amount++;
		}
	}
	return amount / 2;
}

template<typename T>
int Graph<T>::getVertexPos(const T& vert)
{
	for (int i = 0; i < this->vertexV.size(); i++)
	{
		if (this->vertexV[i] == vert) return i;
	}
	return -1;
}

template<typename T>
int Graph<T>::getWeight(const T& vert_1, const T& vert_2)
{
	if (this->isEmpty()) return 0;

	int vert_1Pos = this->getVertexPos(vert_1);
	int vert_2Pos = this->getVertexPos(vert_2);

	if (vert_1Pos == -1 || vert_2Pos == -1)
	{
		std::cout << "One of Node doesnt exist" << std::endl;
		return 0;
	}
	return this->adjMatrix[vert_1Pos][vert_2Pos];
}

template<typename T>
std::vector<T> Graph<T>::getNbrs(const T& vert)
{
	std::vector<T> NbrsVect;
	int pos = this->getVertexPos(vert);
	if (pos != -1)
	{
		for (int i = 0; i < this->vertexV.size(); i++)
			if (this->adjMatrix[pos][i] != 0) 
				NbrsVect.push_back(this->vertexV[i]);
	}
	return NbrsVect;
}

template<typename T>
void Graph<T>::print()
{
	if (!this->isEmpty())
	{
		std::cout << "Adjustment Matrix: " << std::endl;
		std::cout << "   ";
		for (int i = 0; i < vertexV.size(); i++)
			std::cout << vertexV[i] << "  ";
		std::cout << std::endl;

		for (int i = 0; i < this->vertexV.size(); i++)
		{
			std::cout << this->vertexV[i] << " ";
			for (int j = 0; j < this->vertexV.size(); j++)
				std::cout << " " << this->adjMatrix[i][j] << " ";
			std::cout << std::endl;
		}
	}
	else std::cout << "Graph is empty" << std::endl;
}

template<typename T>
void Graph<T>::dijkstra(const Graph<T>& graph, const T& source) {
	int n = getAmountVertexes();

	std::vector<int> distances(n, std::numeric_limits<int>::max());
	distances[getVertexPos(source)] = 0;

	std::vector<bool> visited(n, false);

	for (int i = 0; i < n - 1; i++) {
		int minDistance = std::numeric_limits<int>::max();
		int minIndex = -1;

		for (int j = 0; j < n; j++) {
			if (!visited[j] && distances[j] < minDistance) {
				minDistance = distances[j];
				minIndex = j;
			}
		}

		if (minIndex == -1)
			break;

		visited[minIndex] = true;
		std::vector<T> neighbors = getNbrs(graph.vertexV[minIndex]);

		for (const T& neighbor : neighbors) {
			int neighborPos = getVertexPos(neighbor);
			int weight = getWeight(graph.vertexV[minIndex], neighbor);

			if (!visited[neighborPos] && distances[minIndex] != std::numeric_limits<int>::max()
				&& distances[minIndex] + weight < distances[neighborPos]) {
				distances[neighborPos] = distances[minIndex] + weight;
			}
		}
	}

	
	std::cout << "shortest way to vertex" << source << ":\n";
	for (int i = 0; i < n; i++) {
		if (distances[i] == std::numeric_limits<int>::max()) {
			std::cout << "vertex " << graph.vertexV[i] << " unachievable" << std::endl;
		}
		else {
			std::cout << "distance to vertex" << graph.vertexV[i] << ": " << distances[i] << std::endl;
		}
	}
}

template<typename T>
void Graph<T>::DFS(T& startVertex, bool* visitedVertes)
{
	std::cout << "Vertex " << startVertex << " is visited\n";
	visitedVertes[this->getVertexPos(startVertex)] = true;
	std::vector<T> neighbors = this->getNbrs(startVertex);
	for (int i = 0; i < neighbors.size(); i++)
	{
		if (!visitedVertes[this->getVertexPos(neighbors[i])])
			this->DFS(neighbors[i], visitedVertes);
	} 
}

template<typename T>
void Graph<T>::BFS(T& startVertex, bool* visitedVertes)
{
	
	if (visitedVertes[this->getVertexPos(startVertex)] == false)
	{
		this->VertexQ.push(startVertex);
		std::cout << "Vertex " << startVertex << " is complete\n";
		visitedVertes[this->getVertexPos(startVertex)] = true;
	}

	std::vector<T> neighbors = this->getNbrs(startVertex);
	this->VertexQ.pop();
	for (int i = 0; i<neighbors.size(); i++)
	{
		if (!visitedVertes[this->getVertexPos(neighbors[i])])
		{
			this->VertexQ.push(neighbors[i]);
			visitedVertes[this->getVertexPos(neighbors[i])] = true;
			std::cout << "Vertex " << neighbors[i] << " is complete\n";
		}
	}
	if (this->VertexQ.empty()) return;
	BFS(VertexQ.front(), visitedVertes);

}

template<typename T>
void Graph<T>::visualizeGraph() {

	int numVertices = vertexV.size();
	if (numVertices == 0)
	{
		std::cout << "Graph is empty" << std::endl;
		return;
	}

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	
	glColor3f(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < numVertices; i++)
	{
		glPushMatrix();
		glTranslatef((i + 1) * WINDOW_WIDTH / (numVertices + 1), WINDOW_HEIGHT / 2, 0);
		glBegin(GL_POLYGON);
		for (int j = 0; j < 360; j++)
		{
			float rad = j * 3.14159 / 180;
			glVertex2f(CIRCLE_RADIUS * cos(rad), CIRCLE_RADIUS * sin(rad));
		}
		glEnd();
		glPopMatrix();

		std::stringstream ss;
		ss << vertexV[i];
		std::string vertexStr = ss.str();

		glColor3f(1.0f, 1.0f, 1.0f);
		glRasterPos2f((i + 1) * WINDOW_WIDTH / (numVertices + 1) - TEXT_OFFSET_X, WINDOW_HEIGHT / 2 + TEXT_OFFSET_Y);
		for (int k = 0; k < vertexStr.size(); k++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, vertexStr[k]);
	}

	
	glColor3f(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < numVertices; i++)
	{
		for (int j = i + 1; j < numVertices; j++)
		{
			if (adjMatrix[i][j] != 0)
			{
				glBegin(GL_LINES);
				glVertex2f((i + 1) * WINDOW_WIDTH / (numVertices + 1), WINDOW_HEIGHT / 2);
				glVertex2f((j + 1) * WINDOW_WIDTH / (numVertices + 1), WINDOW_HEIGHT / 2);
				glEnd();

				std::stringstream ss;
				ss << adjMatrix[i][j];
				std::string weightStr = ss.str();

				float midpointX = ((i + 1) * WINDOW_WIDTH / (numVertices + 1) + (j + 1) * WINDOW_WIDTH / (numVertices + 1)) / 2;
				float midpointY = WINDOW_HEIGHT / 2;

				glColor3f(0.0f, 0.0f, 0.0f);
				glRasterPos2f(midpointX - TEXT_OFFSET_X, midpointY + TEXT_OFFSET_Y);
				for (int k = 0; k < weightStr.size(); k++)
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, weightStr[k]);
			}
		}
	}

	glFlush();
}