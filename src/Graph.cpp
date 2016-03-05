#include "Graph.h"
#include "Room.h"

#include <algorithm>
#include <iterator>
#include <functional>

template<class T>
Graph<T>::Graph()
{}

template<class T>
Graph<T>::Graph(std::vector<T> nodes)
{
	for (T node : nodes)
		this->nodes.push_back(Node{ std::move(node) }); // Affect the vector's reference instead ?
}

//This will find every neighbors around every node. O(n²)
template<>
void Graph<Room>::findNeighbors()
{
	for (auto& node1 : nodes)
		for (auto& node2 : nodes)
		{
			if (node1 == node2)
				continue;
			if (node1.content.distance(node2.content) < THRESHOLD)
				node1.neighbors.push_back(&node2);
		}
}

template<>
std::vector<std::vector<bool>> Graph<Room>::generateCorridors(std::vector<std::vector<bool>> arr)
{
	for (Graph<Room>::Node room : Graph<Room>::nodes)
	{
		for (Graph<Room>::Node* neighbor : room.neighbors)
		{
			int x = room.content.middle().x - neighbor->content.middle().x;
			int y = room.content.middle().y - neighbor->content.middle().y;
			int i = 0;
			for (; i < x; i++)
				arr[room.content.middle().x + i][room.content.middle().y] = true;
			for (int j = 0; i < y; j++)
				arr[room.content.middle().x + i][room.content.middle().y + j] = true;
		}
	}
	return arr;
}

/*
 * Note: The resulting Graph will only contain unidirectional links
 *
 * e.g.
 * A has B in it's neighbors
 * B will NOT have A in it's neighbors
 */
template<class T>
void Graph<T>::mst()
{
	std::vector<Node*> new_neighbors{nodes.size(), nullptr};
	new_neighbors[0] = &nodes[0];

	// Recursive function - Depth Search First
	std::function<void(Node*)> DSF = 
		[&](Node* node)
	{
		for (Node* next : node->neighbors)
		{
			auto position = next - &nodes[0];
			if(new_neighbors[position] == nullptr)
			{
				// Construct a new node with it's parent
				new_neighbors[position] = node;
				DSF(next);
			}
		}
	};

	DSF(&nodes.front());

	// Assign new neighbors, 0 is the starting point so no neighbor for this node
	nodes[0].neighbors.clear();
	for(size_t i=1; i<nodes.size(); ++i)
	{
		nodes[i].neighbors.clear();
		if(new_neighbors[i] != nullptr)
			nodes[i].neighbors.push_back(new_neighbors[i]);
	}
}

// Explicit declaration of template use
template class Graph<Room>;
