#include "Floor.h"
#include "Graph.h"
#include "Room.h"

#include <iostream>
#include <vector>
#include <random>

using namespace std;
Floor GenerateFloor(int, int, int, int);
double NormalizedRandom();

int main(int argc, char **argv)
{
	cout << "Graph tests" << endl;

	Graph<Room> graph();
	Graph<Room>::Node node;
	node.content.width = 3;


	cout << "Room tests" << endl;

	Room r1, r2, r3;

	r1.height = 2;
	r1.width = 2;
	r1.position.x = 1;
	r1.position.y = 1;

	r2.height = 3;
	r2.width = 3;
	r2.position.x = 3;
	r2.position.y = 3;

	vector<Room> rooms = { r1, r2 };

	/* FIXME clang causes "Illegal instruction" (with make) */

	//Point p = r1.GetSteeringNewPosition(rooms);
	//cout << "x: " << p.x << endl << "y: " << p.y << endl;


	cout << "Floor tests" << endl;

	Floor f1 = GenerateFloor(30, 5, 10, 20);

	auto arr = f1.toArray();

	cout << "toArray" << endl;
	for (auto row : arr) {
		for (auto col : row)
			cout << col;
		cout << endl;
	}

	//TEST ROOM GENERATION
	//cout << endl << "Room generation tests" << endl;

	int x;
	cin >> x;

	return 0;
}

Floor GenerateFloor(int nbCells, int minSize, int maxSize, int posRadius)
{
	vector<Room> rooms;
	for (int i = 0; i < nbCells; i++)
	{
		int width = std::max((int)round(NormalizedRandom() * maxSize), minSize);
		int height = std::max((int)round(NormalizedRandom() * maxSize), minSize);

		double t = NormalizedRandom() * 2 * 3.14159265358979323846;
		double r = posRadius * sqrt(NormalizedRandom());

		int x = round(r * cos(t));
		int y = round(r * sin(t));

		rooms.push_back(Room{ width, height, x, y });
	}
	return Floor{ rooms };
}

double NormalizedRandom()
{
	std::default_random_engine generator;
	std::normal_distribution<double> distribution(0.5, 0.5);
	double x = distribution(generator);
	while (x > 1 || x < 0)
		x = distribution(generator);

	return x;
}
