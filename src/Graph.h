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
    typedef struct Node {
        T content;
        std::vector<T> neighbors;
        // TODO Parametric constructor with move semantic
        Node()
        {}
    } Node;

    //Graph() = delete;	// Propably will be constructed from provided nodes 
    // (e.g. stream, pre-allocated)
    
    void findNeighbour();
    void steer();		// Apply the steering behavior(ish) algorithm
private:
    int THREASHOLD = 50;
    std::vector<Node> nodes;
};

