#include "graph.h"


int main()
{
	graph g1(10);
	g1.create_density(40);
	g1.print_mat();
	vector<int> solution = g1.dijkstra(0);
	cout << "Dijkstra shortest path: ";
	for (int i = 0; i < solution.size(); i++)
	{
		cout << solution[i] << " " ;
	}
	return 0;
}