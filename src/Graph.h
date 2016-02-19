#pragma once
#include <ostream>
#include <vector>
#include <random>

/**
 * @file Graph.h
 * @date feb. 2016
 * @brief Simple graph to apply the steering behavior algorithm.
 *
 */
template<class T>
class Graph
{
    class Node {
		public:
			T content;
			std::vector<Node> neighbors;

			template<class ... Args>
			Node(Node val, Args &&  ... args)
				: content{val.content}, neighbors{args...}
			{}

			Node(T && val)
				: content{std::move(val)}
			{}

			// FIXME Only check for T for now
			bool operator==(const Node& other)
			{ return content == other.content; }
			bool operator!=(const Node& other)
			{ return !(*this == other); }
	};

public:


    //Graph() = delete;	// Propably will be constructed from provided nodes 
    // (e.g. stream, pre-allocated)
	Graph();
    Graph(int nbCells, int minSize, int maxSize, int posRadius);
    
    void findNeighbors();
    void steer();		// Apply the steering behavior(ish) algorithm
    double NormalizedRandom();
	Graph<T> mst(); // Returns a new Graph, Minimum Spanning Tree of *this 
					// TODO Control the memory that the mst will use to 
					// generate the new Graph

	friend std::ostream& operator<<(std::ostream& os, const Graph<T>& graph);

private:
    int THRESHOLD = 50;
    std::vector<Node> nodes;
    std::default_random_engine generator;

	void GenerateRooms(int nbCells, int minSize, int maxSize, int posRadius);
};

