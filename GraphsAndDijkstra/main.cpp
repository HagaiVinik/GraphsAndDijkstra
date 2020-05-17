#include "graph.h"


int main()
{
	graph g1(10);
	g1.create_density(40);
	g1.print_mat();
	vector<int> solution = g1.dijkstra(0);
	
	return 0;
}
