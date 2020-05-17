/*
*	TASK: IMPLEMENT A GRAPH OBJECT WITH DIJKSTRA METHOD IN IT.
*	AUTHOR: Hagai Vinik.
*	DATE: 06.05.2020
*
*	Basic problem: Write a set of constructors for declaring and initializing a graph.
*	An edge will have a positive cost that is its distance.
*	Have a procedure that produces a randomly generated set of edges with positive distances.
*	Assume the graphs are undirected.
*	The random graph procedure should have edge density as a parameter and
*		distance range as a parameter.
*	So a graph whose density is 0.1 would have 10% of its edges picked at random
*		and its edge distance would be selected at random from the distance range.
*	The procedure should run through all possible undirected edges, say (i,j) and
*		place the edge in the graph if a random probability calculation is less than the density.
*	Compute for a set of randomly generated graphs an average shortest path.
*/


#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <set>

const int NO_EDGE = 0;
const int INFINITY_VAL = 10001;
/*
	Positive cost - above zero
*/

using namespace std;


class graph
{
private:
	vector<vector<int>> matrix;
	int num_of_vertices;
	int num_of_edges;
	int density;

public:
	graph(int size);
	~graph() {}
	void init_graph();
	void create_density(int density);
	void generate_cost(int source, int dest);
	bool adjacent(int source, int dest);
	int get_cost(int source, int dest);
	void print_mat();

	vector<int> get_neighbors(int source);
	int get_closest_neighbor(int vertex);
	void add_edge(int source, int dest, int cost);
	void delete_edge(int source, int dest);

	int get_num_of_vertices() { return num_of_vertices; }
	int get_num_of_edges() { return num_of_edges; }
	vector<int> dijkstra(int source);
};


