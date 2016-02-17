#include "Graph.h"
#include "Room.h"
#include <math.h>
#include <algorithm>
#include <random>

template<>
Graph<Room>::Graph(int nbCells, int minSize, int maxSize, int posRadius)
{
    Graph::GenerateRooms(nbCells, minSize, maxSize, posRadius);
}

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
