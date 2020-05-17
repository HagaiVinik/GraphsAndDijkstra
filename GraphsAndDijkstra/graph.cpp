#include "graph.h"

//Constructor
graph::graph(const int size)
{
	num_of_vertices = size;
	density = 0;
	num_of_edges = 0;
	srand(time(NULL));
	solution.resize(size);
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

int graph::get_closest_neighbor(vector<int> distance, vector<bool> is_visited)
{
	int min_distance = MAX_DISTANCE;
	int closest_neighbor;
	for (int i = 0; i < num_of_vertices; i++)
	{
		if (distance[i] <= min_distance && is_visited[i] == false)
		{
			closest_neighbor = i;
			min_distance = distance[i];
		}
	}
	return closest_neighbor;
}


vector<int> graph::dijkstra(int source)
{
	vector<int>distance;
	vector<bool> is_visited;

	distance.resize(num_of_vertices);
	is_visited.resize(num_of_vertices);

	for (int i = 0; i < num_of_vertices; i++)
	{
		distance[i] = MAX_DISTANCE;
		is_visited[i] = false;
	}
	distance[source] = 0;

	for (int u = 0; u < num_of_vertices - 1; u++)
	{
		int vertex = get_closest_neighbor(distance,is_visited);
		is_visited[vertex] = true;

		for (int v = 0; v < num_of_vertices; v++)
		{
			// check: if vertex wasnt visited, if there is an edge, if distance was init,
			//			if total distance is smaller then current. THEN UPDATE!
			if (!is_visited[v] && matrix[u][v] && distance[u] != INFINITY_VAL &&
				distance[u] + matrix[u][v] < distance[v])
				distance[v] = distance[u] + matrix[u][v];
		}
	}
	save_solution(distance);
	print_solution();
	return distance;
}

void graph::save_solution(vector<int> distance)
{
	for (int i = 0; i < num_of_vertices; i++)
	{
		solution[i] = distance[i];
	}
}

void graph::print_mat()
{
	cout << "graph:" << endl;
	for (int i = 0; i < num_of_vertices; i++)
	{
		for (int j = 0; j < num_of_vertices; j++)
			cout << matrix[i][j] << "	";
		cout << endl;
	}
	cout << endl << endl;
}

void graph::print_solution()
{
	cout << "Vertex:			Distance from source:" << endl;
	for (int i = 0; i < num_of_vertices; i++)
		cout << i << " 			" << solution[i] << endl;
}