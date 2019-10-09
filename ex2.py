#!/usr/bin/python3

import sys
import math

def dijkstra(adj, n, m, v):
    costs = [math.inf] * n
    costs[v] = 0

    v_open = []
    for i in range(0, n):
        v_open.append(i)

    while len(v_open) != 0:
        closest = v_open[0]
        for o in v_open:
            closest = costs[o] < costs[closest] if o else closest
        if closest in v_open:
            v_open.remove(closest)
        for o in v_open:
            if adj[closest * n + o] != 0:
                costs[o] = min([costs[o], costs[closest] + adj[closest * n + o]])

    return costs

def solve(adj, n, m, k, c):
    costs = dijkstra(adj, n, m, k)
    return costs[c - 1]

n = 0
m = 0
k = 0
c = 0

while (True):

    line = sys.stdin.readline().split()
    n = int(line[0])
    m = int(line[1])
    c = int(line[2])
    k = int(line[3])

    if n == 0 and m == 0 and c == 0 and k == 0:
        break

    adj = [0] * (n * n)

    for i in range(0, m):

        u = 0
        v = 0
        t = 0

        edge = sys.stdin.readline().split()
        u = int(edge[0])
        v = int(edge[1])
        t = int(edge[2])

        adj[u * n + v] = t
        adj[v * n + u] = t

        print(solve(adj, n, m, c, k))
