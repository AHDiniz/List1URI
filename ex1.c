#include <stdio.h>
#include <stdlib.h>

typedef struct stack
{
	int top, size;
	int *data;
} Stack;

Stack CreateStack(int size);
void Push(Stack *s, int i);
int Pop(Stack *s);
unsigned char Empty(Stack s);
void DestroyStack(Stack s);

typedef struct graph
{
	unsigned char *adjacencies;
	int n, m;
	int k;
} Graph;

#define SET(g, i, j) g.adjacencies[i * g.n + j] = 1
#define GET(g, i, j) g.adjacencies[i * g.n + j]

Graph ReadGraph();
int ConnectedComponents(Graph g);
void DepthFirstSearch(Graph g, int v, unsigned char *visited);
void DestroyGraph(Graph g);

int main(void)
{
	int cases = 0;
	scanf("%d\n", &cases);

	for (int i = 0; i < cases; ++i)
	{
		printf("Case #%d:\n", i + 1);
		Graph g = ReadGraph();
		printf("%d connected components\n\n", ConnectedComponents(g));
		DestroyGraph(g);
	}

	return 0;
}

Graph ReadGraph(void)
{
	Graph g;

	scanf("%d %d\n", &g.n, &g.m);

	printf("%d %d\n", g.n, g.m);

	g.adjacencies = malloc(sizeof(unsigned char) * g.n * g.n);

	for (int i = 0; i < g.n * g.n; i++)
		g.adjacencies[i] = 0;

	for (int i = 0; i < g.m; i++)
	{
		int u, v;
		scanf("%d %d\n", &u, &v);
		SET(g, u - 97, v - 97);
	}

	return g;
}

int ConnectedComponents(Graph g)
{
	int result = 0;

	unsigned char *visited = malloc(sizeof(unsigned char) * g.n);
	for (int i = 0; i < g.n; i++)
		visited[i] = 0;

	for (int i = 0; i < g.n; i++)
	{
		if (!visited[i])
		{
			DepthFirstSearch(g, i, visited);
			result++;
		}
	}

	free(visited);

	return result;
}

void DestroyGraph(Graph g)
{
	free(g.adjacencies);
}

void DepthFirstSearch(Graph g, int v, unsigned char *visited)
{
	Stack s = CreateStack(g.n);

	printf("%c, ", v + 97);

	Push(&s, v);
	visited[v] = 1;

	while (!Empty(s))
	{
		int u = Pop(&s);
		
		if (!visited[u]) visited[u] = 1;

		for (int i = 0; i < g.n; i++)
		{
			if (!visited[i] && GET(g, u, i))
			{
				printf("%c, ", i + 97);
				Push(&s, i);
			}
		}
	}
	printf("\n");

	DestroyStack(s);
}

Stack CreateStack(int size)
{
	Stack s;

	s.size = size;
	s.top = -1;
	s.data = malloc(sizeof(int) * size);

	return s;
}

void Push(Stack *s, int i)
{
	if (s->top + 1 >= s->size)
		return;
	
	s->data[++s->top] = i;
}

int Pop(Stack *s)
{
	if (s->top < 0)
		return -1;
	
	return s->data[s->top--];
}

unsigned char Empty(Stack s)
{
	return s.top < 0;
}

void DestroyStack(Stack s)
{
	free(s.data);
}