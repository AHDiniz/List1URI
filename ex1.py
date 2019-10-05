#!/usr/bin/python3

import sys

v = 0
e = 0
cases = 0
adj = []
visited = []

cases = int(sys.stdin.readline())

def connected_components():

    result = 0

    for vertex in range(0, v):

        if not visited[vertex]:
            depth_first_search(vertex)
            print()
            result += 1

    return result

def depth_first_search(vertex):

    visited[vertex] = True

    print("%c" % (chr(vertex + 97)), end = ", ")

    for i in range(0, v):
        if not visited[i] and (adj[vertex * v + i] == 1 or adj[i * v + vertex] == 1):
            depth_first_search(i)

    pass

for case in range(0, cases):

    adj.clear()
    visited.clear()

    line = sys.stdin.readline().split()
    v = int(line[0])
    e = int(line[1])

    adj = [0] * (v * v)

    visited = [False] * v

    for i in range(0, e):
        vertices = sys.stdin.readline().split()
        u, j = ord(vertices[0]) - 97, ord(vertices[1]) - 97
        adj[u * v + j] = 1

    print("Case #%d:" % (case + 1))
    cc = connected_components()
    end = "\n\n"
    if (case == cases - 1):
        end = "\n"
    print("%d connected components" % (cc), end = end)
