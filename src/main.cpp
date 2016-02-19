#include "Floor.h"
#include "Graph.h"
#include "Room.h"

#include <iostream>
#include <vector>
#include <random>

using namespace std;
Floor GenerateFloor(int, int, int, int);
double NormalizedRandom(default_random_engine&, normal_distribution<double>&);

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
    
    r3.height = 2;
    r3.width = 2;
    r3.position.x = 1;
    r3.position.y = 2;
    

    vector<Room> rooms = { r1, r2, r3 };

    /* FIXME clang causes "Illegal instruction" (with make) */

	//Floor f1{ rooms };
 //   f1.toOutput(cout);
 //   
 //   //Test, a room is now out
 //   Point p = r1.GetSteeringNewPosition(rooms);
 //   cout << "x: " << p.x << endl << "y: " << p.y << endl;
 //   char s;
 //   while (p != r1.position)
 //   {
 //       r1.position = p;
 //       rooms = {r1, r2, r3 };
 //       f1.rooms = rooms;
 //       f1.toOutput(cout);
 //       rooms = {r2,r3};
 //       p = r1.GetSteeringNewPosition(rooms);
 //       cout << "x: " << p.x << endl << "y: " << p.y << endl;
 //       cin >> s;
 //   }

	//Room generation tests
	cout << endl << endl << "Floor generation..." << endl;
	Floor f2 = GenerateFloor(30, 5, 10, 20);
	f2.toOutput(cout);

	int x;
	cin >> x;

	return 0;
}

Floor GenerateFloor(int nbCells, int minSize, int maxSize, int posRadius)
{
	random_device rd;
	default_random_engine generator(rd());
	normal_distribution<double> distribution(5.0, 2.0);
	vector<Room> rooms;

	for (int i = 0; i < nbCells; i++)
	{
		int width = max((int)round(NormalizedRandom(generator, distribution) * maxSize), minSize);
		int height = max((int)round(NormalizedRandom(generator, distribution) * maxSize), minSize);

		double t = NormalizedRandom(generator, distribution) * 2 * 3.14159265358979323846;
		double r = posRadius * sqrt(NormalizedRandom(generator, distribution));

		int x = round(r * cos(t)) + posRadius;
		int y = round(r * sin(t)) + posRadius;

		rooms.push_back(Room{ width, height, x, y });
	}
	return Floor{ rooms };
}

double NormalizedRandom(default_random_engine& generator, normal_distribution<double>& distribution)
{
	double x = distribution(generator);
	while (x > 1 || x < 0)
		x = distribution(generator);
	return x;
}
