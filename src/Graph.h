#pragma once
#include "Floor.h"

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
		std::vector<Node*> neighbors;

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

	Graph<T>();

	Graph<T>(std::vector<T> rooms);

	void findNeighbors();

	void mst();
	
	friend std::ostream& operator<<(std::ostream& os, const Graph& graph)
	{
		for (auto node : graph.nodes)
		{
			os << node.content << std::endl;
			for (auto neighbor : node.neighbors)
				os << '\t' << neighbor->content << std::endl;
		}
		return os;
	}

	std::vector<std::vector<bool>> generateCorridors(Floor& floor);

private:

	float THRESHOLD = 50;

	std::vector<Node> nodes;
};
