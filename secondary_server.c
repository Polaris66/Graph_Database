#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

enum MessageType
{
    CLIENT_MESSAGE = 0,
    LOAD_BALANCER_MESSAGE = 1
};

enum OperationNumber
{
    READ_OPERATION = 0,
    WRITE_OPERATION = 1
};

enum SecondaryServerNumber
{
    SERVER_1 = 1,
    SERVER_2 = 2
};

// Message Structure
struct Message
{
    long sourceEntity;   // Sent from Client or Load Balancer
    int sequenceNumber;  // Request Number; Unique for each client request
    int operationNumber; // Operation Number
    int targetServer;    // Secondary Server 1 or 2
    char payload[256];   // Graph FileName
};

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
    if (SERVER_NUMBER != SERVER_1 && SERVER_NUMBER != SERVER_2)
    {
        fprintf(stderr, "ERROR: INVALID SECONDARY SERVER NUMBER! ONLY 1 or 2 ALLOWED.\n");
        exit(EXIT_FAILURE);
    }

    // Key for the message queue (make sure it matches the key used by the load balancer)
    key_t key = ftok("msgq", 'K');
    if (key == -1)
    {
        perror("ERROR: Couldn't make the Message Queue Key!");
        exit(EXIT_FAILURE);
    }

    // Create or get the message queue
    int msgQueueID = msgget(key, 0666);
    if (msgQueueID == -1)
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
        if (msgrcv(msgQueueID, &receivedMessage, sizeof(receivedMessage) - sizeof(long), SERVER_NUMBER, 0) == -1)
        {
            if (errno != EINTR)
            {
                // EINTR is expected when the process is interrupted by a signal
                perror("ERROR: SOME ERROR OCCURED!");
                exit(EXIT_FAILURE);
            }
        }
        else
        {

            printf("Received Message:\n");
            printf("Type: %ld\n", receivedMessage.sourceEntity);
            printf("Sequence Number: %d\n", receivedMessage.sequenceNumber);
            printf("Operation Number: %d\n", receivedMessage.operationNumber);
            printf("Target Server: %d\n", receivedMessage.targetServer);
            printf("Payload: %s\n", receivedMessage.payload);

            printf("Sending response back to the client...\n");
        }
    }

    return 0;
}