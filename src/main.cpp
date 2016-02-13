#include "Floor.h"
#include "Graph.h"
#include "Room.h"

#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv)
{
	cout << "Graph tests" << endl;

	Graph<Room> graph;
	Graph<Room>::Node node;
	node.content.width = 3;


	cout << "Room tests" << endl;

	Room r1,r2, r3;

	r1.height = 2;
	r1.width = 2;
	r1.position.x = 1;
	r1.position.y = 1;

	r2.height = 3;
	r2.width = 3;
	r2.position.x = 3;
	r2.position.y = 3;

	vector<Room> rooms = {r1, r2};

	/* FIXME clang causes "Illegal instruction" (with make) */

	//Point p = r1.GetSteeringNewPosition(rooms);
	//cout << "x: " << p.x << endl << "y: " << p.y << endl;


	cout << "Floor tests" << endl;

	Floor f1(rooms);
	
	auto arr = f1.toArray();

	cout << "toArray" << endl;
	for (auto row : arr) {
		for (auto col : row)
			cout << col;
		cout << endl;
	}

    return 0;
}
