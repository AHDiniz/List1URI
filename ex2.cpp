#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

class Graph
{
public:
	Graph(int n, int m, int c);

	void set(int u, int v, int c);
	int get(int u, int v);
	int cost(int k);
private:
	int dijkstra(int k, int c);

	int n, m, c;
	std::vector<int> adj;
};

int main(void)
{
	while (true)
	{
		int n, m, c, k;
		std::cin >> n >> m >> c >> k;

		if (n == 0 && m == 0 && c == 0 && k == 0)
			break;

		Graph g(n, m, c);

		for (int i = 0; i < m; ++i)
		{
			int u, v, c;
			std::cin >> u >> v >> c;
			g.set(u, v, c);
		}

		std::cout << g.cost(k) << std::endl;
	}

	return 0;
}

Graph::Graph(int n, int m, int c)
{
	this->n = n;
	this->m = m;
	this->c = c;

	for (int i = 0; i < n * n; ++i)
		adj.push_back(0);
}

void Graph::set(int u, int v, int c)
{
	adj[u * n + v] = c;
	adj[v * n + u] = c;
}

int Graph::get(int u, int v)
{
	return adj[u * n + v];
}

int Graph::cost(int k)
{
	std::vector<int> costs;
	for (int i = 0; i < c; ++i)
		costs.push_back(dijkstra(k, c));
	std::sort(costs.begin(), costs.end());
	return costs[0];
}

int Graph::dijkstra(int k, int c)
{
	std::vector<int> open;
	std::vector<int> closed;
	std::vector<int> prev;
	std::vector<int> d;
	for (int i = 0; i < n; ++i)
	{
		d.push_back(std::numeric_limits<int>::max());
		open.push_back(i);
		prev.push_back(-1);
	}

	while (open.size() > 0)
	{
		int closest = 0;
		for (int i = 0; i < n; ++i)
		{
			int adjCost = get(k, i);
			closest = (adjCost < closest) ? adjCost : closest;
		}
		
	}
}
