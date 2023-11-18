#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <pthread.h>

typedef struct Payload
{
    int sequence_number;
    int operation_number;
    char graph_file_name[1024];
} Payload;

// Message Structure Definition
typedef struct Message
{
    long mtype;
    Payload payload;
} Message;


int main(int argc, char *argv[])
{
    // Check if the CL arg is present or not
    if (argc != 2)
    {
        fprintf(stderr, "ERROR: COMMAND LINE ARGUMENT NOT GIVEN PROPERLY\n");
        fprintf(stderr, "USAGE: ./secondary_server.bin <secondary_server_number>\n");
        exit(0);
    }

    // Get the Secondary Server Number
    int SERVER_NUMBER = atoi(argv[1]);
    if (SERVER_NUMBER != 1 && SERVER_NUMBER != 2)
    {
        fprintf(stderr, "ERROR: INVALID SECONDARY SERVER NUMBER! ONLY 1 or 2 ALLOWED.\n");
        exit(0);
    }

    // Key for the message queue (make sure it matches the key used by the load balancer)
    key_t key = ftok("msgq", 65);

    // Create or get the message queue
    int msg_id = msgget(key, 0666);
    if (msg_id == -1)
    {
        perror("ERROR: Couldn't find the Message Queue!");
        exit(1);
    }

    printf("Secondary Server %d Unleashing Pure Power 💥💻🔥\n", SERVER_NUMBER);

    // Main Loop
    while (true)
    {
        // Receive a message from the message queue
        Message m;
        // Receive Message;
		int fetchRes = msgrcv(msg_id, &m, sizeof(m.payload), SERVER_NUMBER + 2, 0);

		// Error Handling
		if (fetchRes == -1)
		{
			perror("Secondary Server could not receive message");
			exit(1);
		}

		printf(
            "\nRecieved message with: \nMessage Type: %d\nSequence Number:%d \nOperation Number:%d \nFile Name:%s\n",m.mtype ,m.payload.sequence_number, m.payload.operation_number, m.payload.graph_file_name);

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

    return 0;
}