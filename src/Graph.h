#pragma once
#include "Floor.h"

#include <ostream>
#include <utility>
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
		T* content;
		std::vector<Node*> neighbors;

		Node(T* content)
			: content{ content }
		{}

		void swap(Node& other)
		{
			std::swap(content, other.content);
			neighbors.swap(other.neighbors);
		}

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

	Graph<T>(std::vector<T> & contents);

	void findNeighbors();

	void mst();
	
	std::vector<std::vector<bool>> generateCorridors(Floor& floor);

	friend std::ostream& operator<<(std::ostream& os, const Graph& graph)
	{
		for (auto node : graph.nodes)
		{
			os << *node.content << std::endl;
			for (auto neighbor : node.neighbors)
				os << '\t' << *neighbor->content << std::endl;
		}
		return os;
	}

private:

	float THRESHOLD = 50;

	std::vector<Node> nodes;
};
