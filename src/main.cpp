#include "Floor.h"
#include "Graph.h"
#include "Room.h"
#include "Helper/TimerRAII.h"

#include <iostream>
#include <vector>
#include <random>
#include <fstream>

using namespace std;

Floor GenerateFloor(int, int, int, int);
double NormalizedRandom(default_random_engine&, normal_distribution<double>&);

int mainNbSalle(int argc, char **argv)
{
    std::ofstream fs("dataSpread.csv");
    fs<<"nbSalle,spread"<<std::endl;
    for(int i = 0; i < 40; i++){
        std::vector<std::vector<bool>> arr;
        Graph<Room> graph;
        Floor f2;
        f2 = GenerateFloor(100 + (i * 10), 5, 10, 20);
        fs<<100 + (i * 10)<<","<<f2.spreadRoom(true)<<std::endl;
    }
}

int mainTime(int argc, char **argv)
{
    std::ofstream fs("data.csv");
    fs<<"nbSalle,gen,spread,graph,findNeibors,mst,corridor"<<std::endl;
    bool toCSV = true;
    ostream& os(fs);
    for(int i = 0; i < 40; i++){
        std::vector<std::vector<bool>> arr;
        Graph<Room> graph;
        Floor f2;
        fs<<100 + (i * 10)<<",";
        {
            TimerRAII all("all",std::cout);
            {
                TimerRAII gen("gen",os,toCSV);
                f2 = GenerateFloor(100 + (i * 10), 5, 10, 20);
            }
            {
                TimerRAII spread("spread",os,toCSV);
                f2.spreadRoom();
            }
            {
                TimerRAII graphT("graph",os,toCSV);
                graph = { f2.rooms };
            }

            {
                TimerRAII findN("findNeigbors",os,toCSV);
                graph.findNeighbors();
            }

            {
                TimerRAII timer("mst",os,toCSV);
                graph.mst();
            }
            {
                TimerRAII corridor("corridor",os,toCSV);
                arr = graph.generateCorridors(f2);
            }
        }
        fs<<std::endl;
    }
    fs.close();
    /*
    for (auto row : arr)
    {
        for (auto col : row)
            cout << (col ? "\u2588" : " ");
        cout << std::endl;
    }
    */
    return 0;
}

int main(int argc, char **argv)
{
	Room r1, r2, r3;
	r1.height = 2;
	r1.width = 2;
	r1.position.x = -1;
	r1.position.y = -1;

	r2.height = 3;
	r2.width = 3;
	r2.position.x = 3;
	r2.position.y = 3;

	r3.height = 2;
	r3.width = 2;
	r3.position.x = 3;
	r3.position.y = 3;

	vector<Room> rooms = { r1, r2, r3 };

	Floor f1(rooms);
	f1.toOutput(cout);

	f1.spreadRoom();

	f1.toOutput(cout);

	cout << endl << endl << "Floor generation..." << endl;
	Floor f2 = GenerateFloor(30, 5, 10, 20);
	f2.toOutput(cout);

	f2.spreadRoom();

	f2.toOutput(cout);

	cout << endl << endl << "Graph generation from Floor" << endl;
	Graph<Room> graph = { f2.rooms };

	cout << endl << "linking neighbors" << endl;
	graph.findNeighbors();

	cout << "Graph generated :" << endl << graph << endl;

	cout << endl << "computing minimum spanning tree" << endl;
    {
        TimerRAII timer("mst",std::cout);
        graph.mst();
    }
	cout << "MST generated :" << endl << graph << endl;

	cout << endl << "generating corridors" << endl;
	auto arr = graph.generateCorridors(f2);

	cout << "done" << endl;

	//Output with corridors
	cout << "toOutput" << std::endl;

	for (auto row : arr)
	{
		for (auto col : row)
			cout << (col ? "\u2588" : " ");
		cout << std::endl;
	}

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
