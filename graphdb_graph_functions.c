#include "graphdb_graph_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void initializeGraph(struct Graph *graph, int vertices)
{
    graph->vertices = vertices;

    // Initialize the adjacency matrix with zeros
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            graph->adjacencyMatrix[i][j] = 0;
        }
    }
}

void addEdge(struct Graph *graph, int start, int end)
{
    // Assuming the graph is undirected
    graph->adjacencyMatrix[start][end] = 1;
    graph->adjacencyMatrix[end][start] = 1;
}

void readGraphFromFile(struct Graph *graph, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Read the number of nodes
    fscanf(file, "%d", &(graph->vertices));

    // Read the adjacency matrix
    for (int i = 0; i < graph->vertices; i++)
    {
        for (int j = 0; j < graph->vertices; j++)
        {
            fscanf(file, "%d", &(graph->adjacencyMatrix[i][j]));
        }
    }

    fclose(file);
}

// Helper function for DFS
void dfsHelper(struct Graph *graph, int vertex, bool visited[])
{
    printf("%d ", vertex + 1); // Assuming nodes are labeled 1, 2, 3, ..., n
    visited[vertex] = true;

    for (int i = 0; i < graph->vertices; i++)
    {
        if (graph->adjacencyMatrix[vertex][i] == 1 && !visited[i])
        {
            dfsHelper(graph, i, visited);
        }
    }
}

// Function to perform Depth-First Search (DFS)
void dfs(struct Graph *graph, int startVertex)
{
    bool visited[MAX_NODES] = {false};

    printf("DFS starting from vertex %d:\n", startVertex + 1);
    dfsHelper(graph, startVertex, visited);
    printf("\n");
}

// Function to perform Breadth-First Search (BFS)
void bfs(struct Graph *graph, int startVertex)
{
    bool visited[MAX_NODES] = {false};
    struct Queue
    {
        int items[MAX_NODES];
        int front;
        int rear;
    } queue;

    // Initialize the queue
    queue.front = -1;
    queue.rear = -1;

    // Enqueue the starting vertex and mark it as visited
    queue.items[++queue.rear] = startVertex;
    visited[startVertex] = true;

    printf("BFS starting from vertex %d:\n", startVertex + 1);

    while (queue.front <= queue.rear)
    {
        // Dequeue a vertex
        int currentVertex = queue.items[queue.front++];
        printf("%d ", currentVertex + 1); // Assuming nodes are labeled 1, 2, 3, ..., n

        // Enqueue adjacent vertices
        for (int i = 0; i < graph->vertices; i++)
        {
            if (graph->adjacencyMatrix[currentVertex][i] == 1 && !visited[i])
            {
                queue.items[++queue.rear] = i;
                visited[i] = true;
            }
        }
    }

    printf("\n");
}