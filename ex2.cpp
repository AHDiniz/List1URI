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
	struct DijkstraResult
	{
		std::vector<int> costs;
		std::vector<int> prevs;
	};

	DijkstraResult dijkstra(int start);

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
	DijkstraResult result = dijkstra(k);
	std::sort(result.costs.begin(), result.costs.end());
	return result.costs[0];
}

Graph::DijkstraResult Graph::dijkstra(int start)
{
	std::cout << "Started Dijkstra" << std::endl;

	DijkstraResult result;

	std::vector<int> open;
	std::vector<int> closed;

	for (int i = 0; i < n; ++i)
	{
		open.push_back(i);
		std::cout << "Open = " << i << std::endl;
		if (i == start) result.costs.push_back(0);
		else result.costs.push_back(INT_MAX);
		result.prevs.push_back(0);
	}

	int closest = start;
	while (open.size() > 0)
	{
		for (int o : open)
		{
			if (o != closest && result.costs[o] < result.costs[closest])
			{
				std::remove(open.begin(), open.end(), o);
				std::cout << open.size() << std::endl;
				closest = o;
			}
		}

		closed.push_back(closest);

		for (int o : open)
		{
			if (get(closest, o))
			{
				int current = result.costs[o];
				int test = result.costs[closest] + get(closest, o);
				int cost = (test < current) ? test : current;
				if (cost < current)
				{
					result.costs[o] = cost;
					result.prevs[o] = closest;
				}
			}
		}
	}

	return result;
}
