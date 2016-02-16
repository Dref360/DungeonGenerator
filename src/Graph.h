#pragma once
#include <vector>
#include <random>

/**
 * @file Graph.h
 * @date feb. 2016
 * @brief Simple graph to apply the steering behavior algorithm.
 *
 * Nodes are dumped into it, treated then ready to be extracted.
 */
template<class T>
class Graph
{
public:
    typedef struct Node {
        T content;
        std::vector<T> neighbors;
        // TODO Parametric constructor with move semantic
        Node()
        {}
        Node(T val)
        {
            content = val;
        }
    } Node;

    //Graph() = delete;	// Propably will be constructed from provided nodes 
    // (e.g. stream, pre-allocated)
    Graph(int nbCells, int minSize, int maxSize, int posRadius);
    
    void findNeighbour();
    void steer();		// Apply the steering behavior(ish) algorithm
    double NormalizedRandom();
private:
    int THREASHOLD = 50;
    std::vector<Node> nodes;
    std::default_random_engine generator;

	void GenerateRooms(int nbCells, int minSize, int maxSize, int posRadius);
};

