#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

class Graph
{
public:
	Graph(int n, int m, int c);

	void set(int u, int v, int c);
	int get(int u, int v);
	int cost(int k);
private:
	int dijkstra(int k, int i);

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
	costs.push_back(dijkstra(k, c));
	for (int i = 0; i < c; ++i)
	{
		costs.push_back(dijkstra(k, i) + dijkstra(i, c));
	}
	std::sort(costs.begin(), costs.end());
	return costs[0];
}

int Graph::dijkstra(int k, int target)
{
	std::cout << "Started Dijkstra" << std::endl;

	std::vector<int> costs;
	std::vector<int> open;
	std::vector<int> closed;

	for (int i = 0; i < n; ++i)
	{
		open.push_back(i);
		if (i == k) costs.push_back(0);
		else costs.push_back(INT_MAX);
	}

	std::cout << "Vectors populated" << std::endl;

	while (open.size() > 0)
	{
		int closest = k;
		std::cout << "Finding closest node" << std::endl;
		/* Finding closest node to k */ {
			for (int o : open)
			{
				if (get(k, o))
				{
					if (costs[closest] < costs[o])
						closest = o;
				}
			}
		}
		closed.push_back(closest);
		std::cout << "Removing node from open" << std::endl;
		/* Removing closest from opened */ {
			for (auto it = open.begin(); it != open.end(); ++it)
			{
				if (*it == closest)
					open.erase(it);
			}
		}
		for (int o : open)
		{
			std::cout << "Updating costs" << std::endl;
			if (get(closest, o))
			{
				int cost = (costs[o] < costs[closest] + get(closest, o)) ? costs[o] : costs[closest] + get(closest, o);
				if (cost < costs[o])
					costs[o] = cost;
			}
		}
	}

	return costs[target];
}
