#pragma once
#include <ostream>
#include <vector>

/**
 * @file Graph.h
 * @date feb. 2016
 * @brief Graph to manipultate nodes
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
			: content{ val.content }, neighbors{ args... }
		{}

		Node(T && val)
			: content{ std::forward<T>(val) }
		{}

		bool operator==(const Node& other) const
		{
			return content == other.content;
		}
		bool operator!=(const Node& other) const
		{
			return !(*this == other);
		}
	};

public:

	//Graph() = delete;	// Propably will be constructed from provided nodes 
	// (e.g. stream, pre-allocated)
	Graph();

	Graph<T>(std::vector<T> rooms);

	void findNeighbors();

	Graph<T> mst(); // Returns a new Graph, Minimum Spanning Tree of *this 
					// TODO Control the memory that the mst will use to 
					// generate the new Graph

	friend std::ostream& operator<<(std::ostream& os, const Graph& graph)
	{
		for (auto node : graph.nodes)
		{
			os << node.content << std::endl;
			for (auto neighbor : node.neighbors)
				os << '\t' << neighbor.content << std::endl;
		}
		return os;
	}

	std::vector<std::vector<bool>> generateCorridors(std::vector<std::vector<bool>> arr);

private:

	float THRESHOLD = 100;

	std::vector<Node> nodes;
};
