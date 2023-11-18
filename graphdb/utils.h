// graphdb_utils.h
#ifndef GRAPHDB_UTILS_H
#define GRAPHDB_UTILS_H

#include <pthread.h>
#include <stdio.h>
#include "structs.h"

// Thread function for BFS
void *handleBFS(void *arg)
{
    struct Payload *payload = (struct Payload *)arg;
    // Implement BFS logic here based on the payload
    printf("Handling BFS for Sequence Number %d\n", payload->sequenceNumber);
    // Additional logic...

    pthread_exit(NULL);
}

// Thread function for DFS
void *handleDFS(void *arg)
{
    struct Payload *payload = (struct Payload *)arg;
    // Implement DFS logic here based on the payload
    printf("Handling DFS for Sequence Number %d\n", payload->sequenceNumber);
    // Additional logic...

    pthread_exit(NULL);
}

#endif // GRAPHDB_UTILS_H