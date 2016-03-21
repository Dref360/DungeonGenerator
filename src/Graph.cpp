#include "Graph.h"
#include "Room.h"
#include "Floor.h"

#include <algorithm>
#include <iterator>
#include <functional>

template<class T>
Graph<T>::Graph(std::vector<T> & contents)
{
	nodes.reserve(contents.size());
	for (auto & content : contents)
		nodes.emplace_back(&content);
}

template<class T>
Graph<T>::Graph()
{
    
}

//This will find every neighbors around every node. O(n²)
template<>
void Graph<Room>::findNeighbors()
{
	auto i = 0;
	while (i < nodes.size())
	{
		for (auto & other : nodes)
			if (nodes[i] != other && 
				nodes[i].content->distance(*other.content) < THRESHOLD)
				nodes[i].neighbors.push_back(&other);

		if (nodes[i].neighbors.empty())
		{
			nodes[i].swap(nodes.back());
			nodes.pop_back();
		}
		else
			++i;
	}
}

template<>
std::vector<std::vector<bool>> Graph<Room>::generateCorridors(Floor& floor) const
{
	auto arr = floor.toArray();

	int minX = abs(floor.MinX());
	int minY = abs(floor.MinY());

	for (const auto & node : nodes)
	{
		const Room & room = *node.content,
				   & next = *(*node.neighbors.begin())->content;

		const int room_x = room.middle().x,
				  room_y = room.middle().y,

				  next_x = next.middle().x,
				  next_y = next.middle().y,

				  dx = room_x + minX + room.distanceX(next),
				  dy = room_y + minY + room.distanceY(next);

		int x = room_x + minX,
		    y = room_y + minY;

		//Horizontal part of corridor
		if (room_x < next_x)
			for (; x < dx; ++x)
				arr[x][y] = true;
		else
			for (; x > dx; --x)
				arr[x][y] = true;

		//Vertical part of corridor
		if (room_y < next_y)
			for (; y < dy; ++y)
				arr[x][y] = true;
		else
			for (; y > dy; --y)
				arr[x][y] = true;
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
