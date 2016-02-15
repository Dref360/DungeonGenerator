#include "Graph.h"
#include "Room.h"
#include <math.h>

template<T>
Graph<T>::Graph(int nbCells, int minSize, int maxSize, int posRadius)
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
void Graph<Room>::findNeibourgh()
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

void Graph<Room>::GenerateRooms(int nbCells, int minSize, int maxSize, int posRadius)
{
    for(int i = 0; i < nbCells; i++)
    {
        int width = round(std::max(NormalizedRandom() * maxSize, minSize));
        int height = round(std::max(NormalizedRandom() * maxSize, minSize));
        
        double t = NormalizedRandom() * 2 * 3.14159265358979323846;
        double r = posRadius * sqrt(NormalizedRandom());
        
        int x = round(r * cos(t));
        int y = round(r * sin(t));
        
        nodes.push_back(Node{Room{width, height, x, y}});
    }
}

double Graph<Room>::NormalizedRandom()
{
    if (useCache)
        return cache;
        
    useCache = true;
    double x = 0, y = 0, w = 0;
    
    do
    {
        x = (rand() / ((double) RAND_MAX)) * 2.0 - 1.0;
        y = (rand() / ((double) RAND_MAX)) * 2.0 - 1.0;
        w = x * x + y * y;
    }
    while (w >= 1.0 || w == 0.0);
     
    w = sqrt( -2.0 * log(w) / w);
    cache = x * w;
    return y * w;
}