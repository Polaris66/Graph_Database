#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <pthread.h>
#include "../graphdb/structs.h"

// pthread_mutex_t writeLock;
// pthread_mutex_t readLock;
// int readerCount = 0;

int main(int argc, char *argv[])
{
	// Define Connection
	key_t key;
	int msg_id;

	// Create Shared Message Queuep
	key = ftok(msgq_file, 65);
	msg_id = msgget(key, 0666 | IPC_CREAT);

	// Error Handling
	if (msg_id == -1)
	{
		perror("Server could not create message queue");
		exit(1);
	}

	// pthread_mutex_init(&writeLock, NULL);
	// pthread_mutex_init(&readLock, NULL);

	while (true)
	{
		Message m;
		// Receive Message
		int fetchRes = msgrcv(msg_id, &m, sizeof(m), ToLoadReceiver, 0);

		printf("%d", m.payload.operationNumber);
		// Error Handling
		if (fetchRes == -1)
		{
			perror("Server could not receive message");
			exit(1);
		}

		// m.MessageType = ToSecondaryServer1;

		// // Send To Server (Either Primary or Secondary)
		// int sendRes = msgsnd(msg_id, &m, sizeof(m), 0);
		
		// // Error Handling
		// if (sendRes == -1)
		// {
		// 	perror("Load Balancer could not send message");
		// 	exit(1);
		// }

		// Payload p = m.payload;

		// pthread_t thread;
		// pthread_attr_t thread_attr;
		// pthread_attr_init(&thread_attr);

		// struct ThreadParams params = {
		// 	.m = m,
		// 	.msg_id = msg_id
		// };

		// int pthread_create(thread, thread_attr, HandleRequest, (void *)&params);
		// pthread_join(thread, NULL);
	}
}

// int HandleRequest(void *params)
// {
// 	struct ThreadParams *threadParams = (struct ThreadParams *)params;
	
// 	Message m = threadParams->m;
// 	int msg_id = threadParams->msg_id;
// 	// int reader;

// 	// if (operationNumber == 1 || operationNumber == 2)
// 	// {
// 	// 	reader = 0;
// 	// 	pthread_mutex_lock(&writeLock);
// 	// 	m.MessageType = ToPrimaryServer;
// 	// }
// 	// else
// 	// {
// 	// 	reader = 1;
// 	// 	pthread_mutex_lock(&readLock);
// 	// 	readerCount++;
// 	// 	if (readerCount == 1)
// 	// 		pthread_mutex_lock(&writeLock);
// 	// 	pthread_mutex_unlock(&readLock);

// 	// 	if (sequenceNumber % 2 == 0)
// 	// 		m.MessageType = ToSecondaryServer1;
// 	// 	else
// 	// 		m.MessageType = ToSecondaryServer2;
// 	// }

// 	m.MessageType = ToSecondaryServer1;

// 	// Send To Server (Either Primary or Secondary)
// 	int sendRes = msgsnd(msg_id, &m, sizeof(m), 0);
// 	// Error Handling
// 	if (sendRes == -1)
// 	{
// 		perror("Load Balancer could not send message");
// 		exit(1);
// 	}

// 	// // Receive Message
// 	// int fetchRes = msgrcv(msg_id, &m, sizeof(m), ToLoadReceiver, 0);

// 	// // Error Handling
// 	// if (fetchRes == -1)
// 	// {
// 	// 	perror("Server could not receive message");
// 	// 	exit(1);
// 	// }

// 	// if (!reader)
// 	// 	pthread_mutex_unlock(&writeLock);
// 	// else
// 	// {
// 	// 	pthread_mutex_lock(&readLock);
// 	// 	readerCount--;
// 	// 	if (readerCount == 0)
// 	// 		pthread_mutex_unlock(&writeLock);
// 	// 	pthread_mutex_unlock(&readLock);
// 	// }

// 	return 0;
// }