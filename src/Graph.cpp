#include "Graph.h"
#include "Room.h"

#include <math.h>
#include <algorithm>
#include <iterator>
#include <functional>
#include <random>

template<class T>
Graph<T>::Graph()
{}

template<>
Graph<Room>::Graph(int nbCells, int minSize, int maxSize, int posRadius)
{
    Graph::GenerateRooms(nbCells, minSize, maxSize, posRadius);
}

template<>
void Graph<Room>::steer()
{
    auto graphCopy = *this;
    
    //While graph changes, steer on every node
	for(Node node : nodes)
		node.content.position;
	
}

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

template<class T>
void Graph<T>::GenerateRooms(int nbCells, int minSize, int maxSize, int posRadius)
{
    for(int i = 0; i < nbCells; i++)
    {
        int width = std::max((int)round(NormalizedRandom() * maxSize), minSize);
        int height = std::max((int)round(NormalizedRandom() * maxSize), minSize);
        
        double t = NormalizedRandom() * 2 * 3.14159265358979323846;
        double r = posRadius * sqrt(NormalizedRandom());
        
        int x = round(r * cos(t));
        int y = round(r * sin(t));
        
        nodes.push_back(Node{Room{width, height, x, y}});
    }
}

template<class T>
double Graph<T>::NormalizedRandom()
{
    std::normal_distribution<double> distribution(0.5, 0.5);
    double x = distribution(generator);
    while (x > 1 || x < 0)
        x = distribution(generator);

    return x;
}


// Explicit declaration of template use
template class Graph<Room>;
