#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct graph
{
	int n, m;
	bool *visited;
	int *adj;
} Graph;

Graph CreateGraph(int n, int m);
void DestroyGraph(Graph g);
int ConnectedComponents(Graph g);
void DepthFirstSearch(Graph *g, int v);

int main(void)
{
	int cases;

	scanf("%d\n", &cases);

	int i;
	for (i = 0; i < cases; ++i)
	{
		printf("Case #%d:\n", i + 1);
		int n, m;
		scanf("%d %d\n", &n, &m);
		Graph g = CreateGraph(n, m);
		int j;
		for (j = 0; j < m; ++j)
		{
			char u, v;
			scanf("%c %c\n", &u, &v);
			g.adj[((int)u - 97) * n + ((int)v - 97)] = 1;
		}

		int col, row;
		for (col = 0; col < n; ++col)
		{
			for (row = 0; row < n; ++row)
			{
				if (g.adj[col * n + row] != 1 && g.adj[col * n + row] != 0)
					g.adj[col * n + row] = 1;
			}
		}

		printf("%d connected components\n\n", ConnectedComponents(g));
		DestroyGraph(g);
	}
}

Graph CreateGraph(int n, int m)
{
	Graph g;

	g.m = m;
	g.n = n;

	g.adj = malloc(sizeof(int) * n * n);
	g.visited = malloc(sizeof(bool) * n);

	return g;
}

void DestroyGraph(Graph g)
{
	free(g.adj);
	free(g.visited);
}

int ConnectedComponents(Graph g)
{
	int result = 0;

	int i;
	for (i = 0; i < g.n; ++i)
	{
		if (!g.visited[i])
		{
			DepthFirstSearch(&g, i);
			printf("\n");
			++result;
		}
	}

	return result;
}

void DepthFirstSearch(Graph *g, int v)
{
	g->visited[v] = true;

	printf("%c, ", ((char)v + 97));

	int i;
	for (i = 0; i < g->n; ++i)
		if (!g->visited[i] && (g->adj[v * g->n + i] || g->adj[i * g->n + v]))
			DepthFirstSearch(g, i);
}
