#include "Graph.h"
#include "Room.h"

#include <algorithm>
#include <iterator>
#include <functional>

template<class T>
Graph<T>::Graph()
{}

//This will find every neighbors around every node. O(n²)
template<>
void Graph<Room>::findNeighbors()
{
    for(auto& node1 : nodes)
    {
        for(auto& node2 : nodes)
        {
            if(&node2 == &node1)
                continue;
            if(node1.content.distance(node2.content) < THRESHOLD)
                node1.neighbors.push_back(node2);
        }
    }
}

template<class T>
Graph<T> Graph<T>::mst()
{
	Graph<T> mst{}; // Initialize new Graph to contain Minimum Spanning Tree

	// FIXME Temporary for empty graph
	if(nodes.empty())
		return mst;

	// Recursive function - Depth Search First
	std::function<void(Node&)> DSF
		= [&](Node& node)
		{
			for(Node& next : node.neighbors)
				if(std::find(std::begin(mst.nodes), 
							 std::end(mst.nodes),
							 next) 
					== std::end(mst.nodes)) // if mst does not contain this node
				{
					// Construct a new node with it's parent
					mst.nodes.emplace_back(next, node);
					DSF(next);
				}
		};

	/*
	 * Note: The resulting Graph will only contain unidirectional links
	 *
	 * e.g.
	 * A has B in it's neighbors
	 * B will NOT have A in it's neighbors
	 */
	DSF(nodes.front());

	return mst;
}

// Explicit declaration of template use
template class Graph<Room>;
