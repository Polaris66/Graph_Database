#ifndef GRAPH_FUNCTIONS_H
#define GRAPH_FUNCTIONS_H
#define MAX_NODES 1000

#include <stdio.h>
#include <stdbool.h>

struct Graph
{
    int vertices;
    int adjacencyMatrix[MAX_NODES][MAX_NODES];
};

void initializeGraph(struct Graph *graph, int vertices);
void addEdge(struct Graph *graph, int start, int end);
void readGraphFromFile(struct Graph *graph, const char *filename);
void bfs(struct Graph *graph, int startVertex);
void dfs(struct Graph *graph, int startVertex);

#endif