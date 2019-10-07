#include <iostream>
#include <vector>
#include <algorithm>

using Components = std::vector<std::vector<int>>;

class Graph
{
public:
	Graph(int n, int m);

	void set(int u, int v);
	int get(int u, int v);
	Components cc(void);
	std::vector<int> dfs(int v);
private:
	int n, m;
	std::vector<char> adj;
	std::vector<bool> visited;
};

int main(void)
{
	int cases;

	std::cin >> cases;

	for (int i = 0; i < cases; ++i)
	{
		std::cout << "Case #" << i + 1 << ":" << std::endl;
		int n, m;
		std::cin >> n >> m;
		Graph g(n, m);

		for (int j = 0; j < m; ++j)
		{
			char u, v;
			std::cin >> u >> v;
			g.set((int)(u - 97), (int)(v - 97));
		}

		Components cc = g.cc();
		for (std::vector<int> component : cc)
		{
			std::cout << (char)(component[0] + 97);
			for (int i = 1; i < component.size(); ++i)
				std::cout << "," << (char)(component[i] + 97);
			std::cout << "," << std::endl;
		}
		std::cout << cc.size() << " connected components" << std::endl << std::endl;
	}

	return 0;
}

Graph::Graph(int n, int m)
{
	this->n = n;
	this->m = m;

	for (int i = 0; i < n * n; ++i)
		adj.push_back(0);
	
	for (int i = 0; i < n; ++i)
		visited.push_back(0);
}

void Graph::set(int u, int v)
{
	adj[u * n + v] = 1;
}

int Graph::get(int u, int v)
{
	return adj[u * n + v];
}

Components Graph::cc(void)
{
	Components result;

	for (int v = 0; v < n; ++v)
	{
		if (!visited[v])
		{
			std::vector<int> component = dfs(v);
			std::sort(component.begin(), component.end());
			result.push_back(component);
		}
	}

	return result;
}

std::vector<int> Graph::dfs(int v)
{
	std::vector<int> stack;
	std::vector<int> result;

	stack.push_back(v);
	result.push_back(v);
	visited[v] = true;

	while (stack.size() != 0)
	{
		int u = stack[stack.size() - 1];
		stack.pop_back();

		for (int i = 0; i < n; ++i)
		{
			if (!visited[i] && (get(u, i) || get(i, u)))
			{
				stack.push_back(i);
				result.push_back(i);
				visited[i] = true;
			}
		}
	}

	return result;
}
