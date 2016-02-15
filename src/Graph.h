#pragma once
#include <vector>

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
	typedef struct {
		T content;
		std::vector<T> neighbors;
		// TODO Parametric constructor with move semantic
        Node(T val)
        {
            content = val;
        }
	} Node;

	//Graph() = delete;	// Propably will be constructed from provided nodes 
						// (e.g. stream, pre-allocated)
                        
    Graph(int nbCells, int minSize, int maxSize, int posRadius);

	void steer();		// Apply the steering behavior(ish) algorithm
    double NormalizedRandom();
private:
	std::vector<Node> nodes;

    void GenerateRooms(int nbCells, int minSize, int maxSize, int posRadius);
    

    int cache = 0;
    bool useCache = true;
};

