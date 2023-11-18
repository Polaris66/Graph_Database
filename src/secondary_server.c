#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <pthread.h>
#include "../graphdb/structs.h"
#include "../graphdb/utils.h"
#include "../graphdb/graph_functions.h"

int main(int argc, char *argv[])
{
    // Check if the CL arg is present or not
    if (argc != 2)
    {
        fprintf(stderr, "ERROR: COMMAND LINE ARGUMENT NOT GIVEN PROPERLY\n");
        fprintf(stderr, "USAGE: ./secondary_server.bin <secondary_server_number>\n");
        exit(EXIT_FAILURE);
    }

    // Get the Secondary Server Number
    int SERVER_NUMBER = atoi(argv[1]);
    if (SERVER_NUMBER != SecondaryServer1 && SERVER_NUMBER != SecondaryServer2)
    {
        fprintf(stderr, "ERROR: INVALID SECONDARY SERVER NUMBER! ONLY 1 or 2 ALLOWED.\n");
        exit(EXIT_FAILURE);
    }

    // Key for the message queue (make sure it matches the key used by the load balancer)
    key_t key = ftok(msgq_file, 65);
    if (key == -1)
    {
        perror("ERROR: Couldn't make the Message Queue Key!");
        exit(EXIT_FAILURE);
    }

    // Create or get the message queue
    int msg_id = msgget(key, 0666);
    if (msg_id == -1)
    {
        perror("ERROR: Couldn't find the Message Queue!");
        exit(EXIT_FAILURE);
    }

    printf("Secondary Server %d Unleashing Pure Power 💥💻🔥\n", SERVER_NUMBER);

    // Main Loop
    while (true)
    {
        // Receive a message from the message queue
        struct Message receivedMessage;
        if (msgrcv(msg_id, &receivedMessage, sizeof(receivedMessage) - sizeof(long), SERVER_NUMBER, 0) == -1)
        {
            if (errno != EINTR)
            {
                // EINTR is expected when the process is interrupted by a signal
                perror("ERROR: SOME ERROR OCCURRED!");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            printf("Received Message:\n");
            printf("Type: %ld\n", receivedMessage.MessageType);
            printf("Sequence Number: %d\n", receivedMessage.payload.sequenceNumber);
            printf("Operation Number: %d\n", receivedMessage.payload.operationNumber);
            printf("Payload: %s\n", receivedMessage.payload.payload);

            printf("Received Message:\n");
            printf("Type: %ld\n", receivedMessage.MessageType);
            printf("Sequence Number: %d\n", receivedMessage.payload.sequenceNumber);
            printf("Operation Number: %d\n", receivedMessage.payload.operationNumber);
            printf("Payload: %s\n", receivedMessage.payload.payload);

            // Handle messages based on Operation Number using threads
            // pthread_t bfsThread, dfsThread;

            // if (receivedMessage.payload.operationNumber == BFS_OPERATION)
            // {
            //     pthread_create(&bfsThread, NULL, handleBFS, (void *)&receivedMessage.payload);
            // }
            // else if (receivedMessage.payload.operationNumber == DFS_OPERATION)
            // {
            //     pthread_create(&dfsThread, NULL, handleDFS, (void *)&receivedMessage.payload);
            // }
            // else
            // {
            //     printf("Unknown Operation Number. Ignoring the message.\n");
            // }
        }
    }

    return 0;
}