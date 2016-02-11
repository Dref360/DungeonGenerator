#pragma once
#include <vector>

/*
 * Description :
 * This Graph is a container to apply the steering behavior algorithm.
 *
 * Use case :
 * Nodes are dumped into it, treated then ready to be extracted.
 *
 */
template<class T>
class Graph
{
public:
	typedef struct {
		typedef struct {int x,y;} distance;
		typedef struct {T content; distance vector;} neighbor;
		T content;
		std::vector<neighbor> neighbors;
		// TODO Parametric constructor with move semantic
	} Node;

	//Graph() = delete;	// Propably will be constructed from provided nodes 
						// (e.g. stream, pre-allocated)

	Graph(/* TODO Some feeding input */);

	void steer();		// Apply the steering behavior(ish) algorithm

private:
	std::vector<Node> nodes;

};

