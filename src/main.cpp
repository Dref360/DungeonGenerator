#include "Floor.h"
#include "Graph.h"
#include "Room.h"
#include "Helper/TimerRAII.h"
#include "Helper/Report.h"

#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <map>

#define debugStream \
    if (true) {} \
    else std::cerr

using namespace std;

/*
 * nbCells : number of desired rooms
 * minSize : minimum size for a room (width and height)
 * maxSize : maximum size for a room (width and height)
 * spread  : caracterizing spacing between rooms
 */
Floor GenerateFloor(const unsigned int nbCells, const unsigned int minSize, const unsigned int maxSize, const float spread)
{
	vector<Room> rooms;
	rooms.reserve(nbCells);

	srand(time(0)); // the seeding could be changed in case there is a heavy load in a short period of time
					// here if 2 requests happen within the same second, results will be identical

	unsigned int n = 1;

	float r = 1,
		  rad_step;

	while (n <= nbCells)
	{
		r += spread;
		rad_step = maxSize / r;

		if (2*M_PI/rad_step > nbCells-n)
			rad_step = 2*M_PI/(nbCells-n);

		for(float rad=0; rad<2*M_PI; rad+=rad_step, ++n)
			rooms.emplace_back(
					max(rand()%maxSize,minSize),
					max(rand()%maxSize,minSize),
					cos(rad)*r,
					sin(rad)*r);
	}

	return Floor{rooms};
}
/*This test the spread algoreithm*/
int mainTour(int argc, char **argv)
{
		map<int,vector<int>> time;
		const int NbSalleInput = 60;
    std::ofstream fs("data.csv");
    fs<<"nbSalle,gen,spread,graph,findNeibors,mst,corridor"<<std::endl;
    bool toCSV = true;
    ostream& os(fs);
		for (size_t x = 0; x < 60; x++) {
    for(int i = 0; i < NbSalleInput; i++){
        std::vector<std::vector<bool>> arr;
        Graph<Room> graph;
        Floor f2;
				int nbSalle = 100 + (i * 10);
        fs<<100 + (i * 10)<<",";
        {
            //TimerRAII all("all",std::cout);
            {
                //TimerRAII gen("gen",os,toCSV);
                f2 = GenerateFloor(100 + (i * 10), 5, 10, 10);
            }
            {
                //TimerRAII spread("spread",os,toCSV);
                auto x = f2.spreadRoom(true);
                time[nbSalle].push_back(x);

            }
            {
                //TimerRAII graphT("graph",os,toCSV);
                graph = { f2.rooms };
            }

            {
                //TimerRAII findN("findNeigbors",os,toCSV);
                graph.findNeighbors();
            }

            {
                //TimerRAII timer("mst",os,toCSV);
                graph.mst();
            }
            {
                //TimerRAII corridor("corridor",os,toCSV);
                arr = graph.generateCorridors(f2);
            }

        }
        fs<<std::endl;
    }
	}

	fs << endl;
	cout<<"Printing Report" << endl;
	fs << "nbSalle,means,std,min,max"<<endl;
	for(int i = 0; i < NbSalleInput; i++){
			int nbSalle = 100 + (i * 10);
			fs<<nbSalle <<",";
			Report rp(time[nbSalle]);
			rp.print(fs,true);
	}

    fs.close();


    return 0;
}
/*This is an example to test the speed of our programm*/
int mainTime(int argc, char **argv)
{
		map<int,vector<int>> time;
		const int NbSalleInput = 60;
    std::ofstream fs("datatime.csv");
    fs<<"nbSalle,gen,spread,graph,findNeibors,mst,corridor"<<std::endl;
    bool toCSV = true;
    ostream& os(fs);
		for (size_t x = 0; x < 60; x++) {
    for(int i = 0; i < NbSalleInput; i++){
        std::vector<std::vector<bool>> arr;
        Graph<Room> graph;
        Floor f2;
				int nbSalle = 100 + (i * 10);
        fs<<100 + (i * 10)<<",";
        {
            TimerRAII all("all",std::cout);
            {
                TimerRAII gen("gen",os,toCSV);
                f2 = GenerateFloor(100 + (i * 10), 5, 10, 10);
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
	}

	fs << endl;
	cout<<"Printing Report" << endl;
	fs << "nbSalle,means,std,min,max"<<endl;
	for(int i = 0; i < NbSalleInput; i++){
			int nbSalle = 100 + (i * 10);
			fs<<nbSalle <<",";
			Report rp(time[nbSalle]);
			rp.print(fs,true);
	}

    fs.close();


    return 0;
}

int main(int argc, char **argv)
{
  cout << argc;
  if(argc < 2)
  {
    std::cout << "Need the number of room!" << endl;
    exit(0);
  }
  cout << argv[1];
	Floor floor = GenerateFloor(atoi(argv[1]), 5, 10, 5);
	floor.spreadRoom();
	Graph<Room> graph = { floor.rooms };
	graph.findNeighbors();
	graph.mst();

	auto arr = graph.generateCorridors(floor);
	for (auto row : arr)
	{
		for (auto col : row)
			cout << (col ? "\u2588" : " ");
		cout << std::endl;
	}
	return 0;
}
