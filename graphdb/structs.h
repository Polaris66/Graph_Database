#pragma once

enum MessageType
{
    ToLoadReceiver = 1,
    ToPrimaryServer = 2,
    ToSecondaryServer1 = 3,
    ToSecondaryServer2 = 4,
    ToClient = 5,
    Cleanup = 6
};

enum SecondaryServer
{
    SecondaryServer1 = 1,
    SecondaryServer2 = 2
};

enum Operation
{
    BFS_OPERATION = 1,
    DFS_OPERATION = 2,
    MODIFY_OPERATION = 3,
    CREATE_OPERATION = 4
};

typedef struct Payload
{
    int sequence_number;
    int operation_number;
    char graph_file_name[100];
} Payload;

// Message Structure Definition
typedef struct Message
{
    long mtype;
    Payload payload;
} Message;


#define MAX_SIZE 1024
#define SHARED_MEMORY_SIZE 1024

char *msgq_file = "progfile";

#include <sys/msg.h>