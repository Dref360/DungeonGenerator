#include "Graph.h"
#include "Room.h"

#include <iostream>

int main(int argc, char **argv)
{
    std::cout << "Hello World" << std::endl;

	Graph<Room> graph;

	Graph<Room>::Node node;
	node.content.width = 3;

    return 0;
}
