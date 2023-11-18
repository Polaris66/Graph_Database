#ifndef GRAPHDB_STRUCTS_H
#define GRAPHDB_STRUCTS_H

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

struct Payload
{
    int sequenceNumber;  // Request Number; Unique for each client request
    int operationNumber; // Operation Number
    char *payload;   // Graph FileName
};

// Message Structure
struct Message
{
    long MessageType;
    struct Payload payload;
};

typedef struct Message Message;
typedef struct Payload Payload;


#define MAX_SIZE 1024
#define SHARED_MEMORY_SIZE 1024

char *msgq_file = "msgq";

#include <sys/msg.h>

#endif // GRAPHDB_STRUCTS.h