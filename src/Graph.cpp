#include "Graph.h"
#include "Room.h"

// Add a trait (e.g. Position) to Room to treat general cases
template<>
void Graph<Room>::steer()
{
    auto graphCopy = *this;
    
    //While graph changes, steer on every node
	for(Node node : nodes)
		node.content.position;
	
}

//This will find every neibourghs around every node. O(n²)
template<>
void Graph<Room>::findNeighbour()
{
    for(auto node1 : nodes)
    {
        for(auto node2 : nodes)
        {
            if(&node2 == &node1)
                continue;
            if(node1.content.distance(node2.content) < THREASHOLD)
                node1.neighbors.push_back(node2.content);
        }
    }
}

// Explicit declaration of template use
template class Graph<Room>;
