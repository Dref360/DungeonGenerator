#include "Graph.h"
#include "Room.h"

template <class T>
Graph<T>::Graph(/* Input */)
{
	
}

// Add a trait (e.g. Position) to Room to treat general cases
template<>
void Graph<Room>::steer()
{
	for(Node node : nodes)
		node.content.position;
	
}

// Explicit declaration of template use
template class Graph<Room>;
