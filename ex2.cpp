#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

#define SWAP(a,b) a^=b^=a^=b

class Graph
{
public:
	Graph(int n, int m);
	void set(int n, int m, int c);
	int get(int n, int m);
	int solve(int k, int c);
private:
	std::vector<int> dijkstra(int v, int c);

	int n, m;
	std::vector<int> adj;
};

int main(void)
{
	int n, m, c, k;
	while (true)
	{
		std::cin >> n >> m >> c >> k;

		if (n == 0 && m == 0 && c == 0 && k == 0) return 0;

		Graph g(n, m);

		for (int i = 0; i < m; ++i)
		{
			int a, b, cost;
			std::cin >> a >> b >> cost;
			g.set(a, b, cost);
			g.set(b, a, cost);
		}

		for (int v = 0; v < c - 1; ++v)
			for (int u = 0; u < n; ++u)
				if (u != v + 1)
					g.set(v, u, 0);

		std::cout << g.solve(k, c) << std::endl;
	}

	return 0;
}

Graph::Graph(int n, int m)
{
	this->n = n;
	this->m = m;

	for (int i = 0; i < n * n; ++i)
		adj.push_back(0);
}

void Graph::set(int n, int m, int c)
{
	adj[n * this->n + m] = c;
}

int Graph::get(int n, int m)
{
	return adj[n * this->n + m];
}

int Graph::solve(int k, int c)
{
	std::vector<int> costs = dijkstra(k, c);

	return (costs[c - 1] == INT_MAX / 2) ? 0 : costs[c - 1];
}

std::vector<int> Graph::dijkstra(int v, int c)
{
	std::vector<int> costs;

	std::vector<int> open;

	for (int i = 0; i < n; ++i)
	{
		open.push_back(i);
		if (i == v) costs.push_back(0);
		else costs.push_back(INT_MAX / 2);
	}

	while (!open.empty())
	{
		int closest = open[0];
		for (int o : open)
			closest = (costs[o] < costs[closest]) ? o : closest;
		open.erase(std::remove(open.begin(), open.end(), closest), open.end());
		if (closest == c - 1) break;
		for (int o : open)
			if (get(closest, o))
				costs[o] = std::min(costs[o], costs[closest] + get(closest, o));
	}

	return costs;
}