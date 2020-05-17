#include "graph.h"


graph::graph(const int size)
{
	num_of_vertices = size;
	density = 0;
	num_of_edges = 0;
	matrix.resize(size);
	for (int i = 0; i < size; i++)
		matrix[i].resize(size);
	init_graph();
}

void graph::init_graph()
{
	for (int i = 0; i < num_of_vertices; i++)
		for (int j = 0; j < num_of_vertices; j++)
			matrix[i][j] = NO_EDGE;
}

bool graph::adjacent(int source, int dest)
{
	if (matrix[source][dest] != NO_EDGE && matrix[dest][source] != NO_EDGE)
		return true;
	return false;
}

int graph::get_cost(int source, int dest)
{
	return matrix[source][dest];
}

vector<int> graph::get_neighbors(int source)
{
	vector<int> neighbors_arr;
	neighbors_arr.resize(NO_EDGE);
	for (int i = 0; i < num_of_vertices; i++)
	{
		if (matrix[source][i] != NO_EDGE)
			neighbors_arr.push_back(matrix[source][i]);
	}
	return neighbors_arr;
}

int graph::get_closest_neighbor(int vertex)
{
	int min_distance = 101;
	int closest_neighbor = -1;
	for (int i = 0; i < num_of_vertices; i++)
	{
		if (vertex != i)
			if (matrix[vertex][i] < min_distance && matrix[vertex][i] > 0)
			{
				closest_neighbor = i;
				min_distance = matrix[vertex][i];
			}
	}
	return closest_neighbor;
}

void graph::add_edge(int source, int dest, int cost)
{
	matrix[source][dest] = cost;
}

void graph::delete_edge(int source, int dest)
{
	matrix[source][dest] = NO_EDGE;
}

void graph::create_density(int density)
{
	num_of_edges = 0;  //Init
	for (int i = 0; i < num_of_vertices; i++)
	{
		for (int j = 0; j < num_of_vertices; j++)
		{
			if (i == j)
				matrix[i][j] = NO_EDGE;
			else if (matrix[i][j] == NO_EDGE)
			{
				int v1 = rand() % 100 + 1;         // v1 in the range 0 to 99
				if (v1 < density)
				{
					generate_cost(i, j);
					num_of_edges++;
				}
			}
		}
	}
}

void graph::generate_cost(int source, int dest)
{
	int val = (rand() % 100) + 1;
	matrix[source][dest] = val;
	matrix[dest][source] = val;
}


vector<int> graph::dijkstra(int source)
{
	vector<int>distance;
	set<int> unvisited_ver;
	distance.resize(num_of_vertices);
	
	for (int i = 0; i < num_of_vertices; i++)
	{
		if (i != source)
		{
			distance[i] = INFINITY_VAL;
			unvisited_ver.insert(i);
		}
	}
	distance[source] = 0;
	int vertex = source;
	int alt_value = -1;
	while (!unvisited_ver.empty())
	{
		vertex = get_closest_neighbor(vertex);
		unvisited_ver.erase(vertex);
		vector<int> vertex_neighbors = get_neighbors(vertex);
		for (int i = 0; i < vertex_neighbors.size(); i++)
		{
			if (distance[vertex] == INFINITY_VAL)			//if not initialized.
				alt_value = matrix[vertex][i];   //value of edge.
			else
				alt_value = distance[vertex] + matrix[vertex][i];

			if (alt_value < distance[i])
				distance[i] = alt_value;
		}
	}
	return distance;
}

void graph::print_mat()
{
	cout << "graph:" << endl;
	for (int i = 0; i < num_of_vertices; i++)
	{
		for (int j = 0; j < num_of_vertices; j++)
			cout << matrix[i][j] << "  ";
		cout << endl;
	}
}


