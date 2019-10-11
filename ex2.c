#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <alloca.h>

#define MIN(i, j) (i < j) ? i : j;
#define INFINITY INT_MAX / 2

typedef struct graph
{
	int n, m;
	int *adj;
} Graph;

#define SET(g, i, j, c) g.adj[i * g.n + j] = c
#define GET(g, i, j) g.adj[i * g.n + j]

Graph CreateGraph(int n, int m);
void DestroyGraph(Graph g);
int Solve(Graph g, int k, int c);

int main(void)
{
	int n, m, c, k;

	while (1)
	{
		int scanRes = scanf("%d %d %d %d\n", &n, &m, &c, &k);

		if (n == 0 && m == 0 && c == 0 && k == 0) break;

		Graph g = CreateGraph(n, m);

		int i;
		for (i = 0; i < m; ++i)
		{
			int u, v, c;
			scanRes = scanf("%d %d %d\n", &u, &v, &c);

			SET(g, u, v, c);
			SET(g, v, u, c);
		}

		int j;
		for (i = 0; i < c; ++i)
			for (j = 0; j < n; ++j)
				if (j != i + 1)
					SET(g, i, j, 0);

		printf("%d\n", Solve(g, k, c));

		DestroyGraph(g);
	}

	return 0;
}

Graph CreateGraph(int n, int m)
{
	Graph g;

	g.n = n;
	g.m = m;

	g.adj = malloc(sizeof(int) * n * n);

	for (int i = 0; i < n * n; ++i)
		g.adj[i] = 0;

	return g;
}

void DestroyGraph(Graph g)
{
	free(g.adj);
}

int Solve(Graph g, int k, int c)
{
	int result = 0;

	/* Executing Dijkstra */ {

		int *costs = alloca(sizeof(int) * g.n);
		int *open = alloca(sizeof(int) * g.n);
		int size = g.n;

		int count;
		for (count = 0; count < g.n; ++count)
		{
			open[count] = count;
			if (count == k) costs[count] = 0;
			else costs[count] = INFINITY;
		}

		while (size > 0)
		{
			// Getting closest open node to start node:
			int closest = open[0];
			int indexOpen;
			for (indexOpen = 0; indexOpen < size; ++indexOpen)
				closest = (costs[indexOpen] < costs[closest]) ? indexOpen : closest;

			// Closing the closest node:
			int remove;
			for (remove = indexOpen; remove < size - 1; ++remove)
				open[remove] = open[remove + 1];
			--size;

			for (indexOpen = 0; indexOpen < size; ++indexOpen)
				if (GET(g, closest, indexOpen))
					costs[indexOpen] = MIN(costs[indexOpen], costs[closest] + GET(g, closest, indexOpen));
		}

		result = costs[c - 1];
	}

	return result;
}
