#pragma once

#include <unordered_map> // for std::unordered_map
#include <vector> // for std::vector
#include <memory> // for std::unique_ptr
#include <utility> // for std::pair
#include <iostream> // for std::cout

//
template <class T>
class Vertex {
public:
	Vertex(const T& obj) : _objAtVertex(obj) {}

	const T& getObjAtVert() const { return _objAtVertex; }
	void setObjAtVert(const T& obj) { _objAtVertex = obj; }
private:
	T _objAtVertex;		// Holds some object at the vertex
};

// Where U is the edge object and T the vertex type
template <class U, class T>
class Edge {
public:
	// Can be constructed with two connecting vertices
	Edge(const Vertex<T>* v1, const Vertex<T>* v2) : _v1(v1), _v2(v2) {}
	// Can be constructed w/ two connecting verts and an edge type
	Edge(const Vertex<T>* v1, const Vertex<T>* v2, const U& objOnEdge) : _v1(v1), _v2(v2), _objOnEdge(objOnEdge) {}

	// Sets the edge's two vertices
	void connectEdgeTo(const Vertex<T>* v1, const Vertex<T>* v2) {
		_v1 = v1;
		_v2 = v2;
	}

	// Tells you if a vertex is one of the edge's verts
	bool isEdgeConnectedTo(const Vertex<T>* vert) const {
		return (_v1 == vert || _v2 == vert);
	}

	// Returns the object on the edge
	const U& getObjOnEdge() const { return _objOnEdge; }
	// Sets the object on the edge
	void setObjOnEdge(const U& obj) { _objOnEdge = obj; }

	// Get the particular verts
	const Vertex<T>* getV1() const { return _v1; }
	const Vertex<T>* getV2() const { return _v2; }
private:
	U _objOnEdge;		// Some arbitrary type representing the edge and/or weight
	const Vertex<T>* _v1;
	const Vertex<T>* _v2;
};

// A graph holding any type of vert and edge implemented using an adjacency list 
// T = vertex data type, U = edge data type
template <class T, class U> 
class Graph {
public:
	// Add a vertex to the graph and returns a pointer to it
	Vertex<T>* addVertex(const T& obj) {
		// Create a new vertex and transfer ownership to the graph
		auto vert = std::make_unique<Vertex<T>>(obj);
		Vertex<T>* vertPtr = vert.get();
		vertices.push_back(std::move(vert));

		// Initalized an empty list for the edges adjacent to this vert
		adjacencyList[vertPtr] = std::vector<Edge<U, T>*>();
		return vertPtr;
	}

	// Add an edge between two verts (undirected by default)
	Edge<U, T>* addEdge(Vertex<T>* v1, Vertex<T>* v2, const U& edgeData = U()) {
		// Create a new edge and transfer ownership to the graph
		auto edge = std::make_unique<Edge<U, T>>(v1, v2, edgeData);
		Edge<U, T>* edgePtr = edge.get();
		edges.push_back(std::move(edge));

		// Add the edge to the adjacency list for both vertices
		adjacencyList[v1].push_back(edgePtr);
		adjacencyList[v2].push_back(edgePtr);
		return edgePtr;
	}

	// Print function to display the graph structure.
	void printGraph() const {
		for (const auto& pair : adjacencyList) {
			const Vertex<T>* vertex = pair.first;
			const auto& edges = pair.second;
			std::cout << "Vertex: " << vertex->getObjAtVert() << "\n";
			for (const auto* edge : edges) {
				// Determine the other vertex connected by this edge.
				const Vertex<T>* other = (edge->getV1() == vertex) ? edge->getV2() : edge->getV1();
				std::cout << "\t-> " << other->getObjAtVert()
						  << " (Edge data: " << edge->getObjOnEdge() << ")\n";
			}
			std::cout << "\n";
		}
	}

	// Getters
	const auto& getAdjacencyList() const { return adjacencyList; }
	const auto& getVertices() const { return vertices; } 
	const auto& getEdges() const { return edges; } 
	Edge<U, T>* getEdgeBetween(Vertex<T>* v1, Vertex<T>* v2) const {
		for (const auto* edge: edges) {
			// Checks the two possible connections
			if (edge->getV1() == v1 && edge->getV2() == v2 || edge->getV1() == v2 && edge->getV2() == v1) {
				return edge.get();
			}
		}
	}

	// Later add remove edge and remove vert functions

private:
	// The graph owns its vertices and edges
	std::vector<std::unique_ptr<Vertex<T>>> vertices;
	std::vector<std::unique_ptr<Edge<U, T>>> edges;

	// Adjacency List where each key is a node and its value is a list of tuples (neighbor, weight)
	// Dictionary (VertexKey : List{(neighbor, weight), ...})
	// 		In this case, the tuples are just represented by the Edge Type
	std::unordered_map<Vertex<T>*, std::vector<Edge<U, T>*>> adjacencyList;
};