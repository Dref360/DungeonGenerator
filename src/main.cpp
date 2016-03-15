#include "Floor.h"
#include "Graph.h"
#include "Room.h"
#include "Helper/TimerRAII.h"

#include <iostream>
#include <vector>
#include <random>
#include <fstream>

using namespace std;

/*
 * nbCells : number of desired rooms
 * minSize : minimum size for a room (width and height)
 * maxSize : maximum size for a room (width and height)
 * spread  : caracterizing spacing between rooms (e.g. 0.5)
 */
Floor GenerateFloor(const unsigned int nbCells, const unsigned int minSize, const unsigned int maxSize, const float spread)
{
	vector<Room> rooms;
	rooms.reserve(nbCells);

	srand(time(0)); // the seeding could be changed in case there is a heavy load in a short period of time
					// here if 2 requests happen within the same second, results will be identical

	unsigned int n = 1;
	while (n <= nbCells)
	{
		const float r = n*spread;
		float rad_step = maxSize / r;
		
		if (2*M_PI/rad_step > nbCells-n)
			rad_step = 2*M_PI/(nbCells-n);

		for(float rad=0; rad<2*M_PI; rad+=rad_step)
		{
			rooms.emplace_back(
					max(rand()%maxSize,minSize),
					max(rand()%maxSize,minSize),
					cos(rad)*r,
					sin(rad)*r);
			++n;
		}
	}

	return Floor{rooms};
}

int mainNbSalle(int argc, char **argv)
{
    std::ofstream fs("dataSpread.csv");
    fs<<"nbSalle,spread"<<std::endl;
    for(int i = 0; i < 40; i++){
        std::vector<std::vector<bool>> arr;
        Graph<Room> graph;
        Floor f2;
        f2 = GenerateFloor(100 + (i * 10), 5, 10, 0.5);
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
                f2 = GenerateFloor(100 + (i * 10), 5, 10, 0.5);
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
//	exit(mainTime(argc,argv));
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
	Floor f2 = GenerateFloor(50, 5, 10, 0.5);
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

