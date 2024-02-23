#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
int sharedResource = 0;
sem_t mutex, writeMutex;
int readerCount = 0;
void* readerFunction(void* threadID);
void* writerFunction(void* threadID);
int main() 
{
    sem_init(&mutex, 0, 1);
    sem_init(&writeMutex, 0, 1);
    pthread_t reader1, reader2, writer1, writer2;
    int id1 = 1, id2 = 2;
    pthread_create(&reader1, NULL, readerFunction, (void*)&id1);
    pthread_create(&reader2, NULL, readerFunction, (void*)&id2);
    pthread_create(&writer1, NULL, writerFunction, (void*)&id1);
    pthread_create(&writer2, NULL, writerFunction, (void*)&id2);
    pthread_join(reader1, NULL);
    pthread_join(reader2, NULL);
    pthread_join(writer1, NULL);
    pthread_join(writer2, NULL);
    sem_destroy(&mutex);
    sem_destroy(&writeMutex);
    return 0;
}
void* readerFunction(void* threadID) 
{
    int readerID = *((int*)threadID);
    for (int i = 0; i < 3; i++) 
	{
        sem_wait(&mutex);
        readerCount++;
        if (readerCount == 1) 
		{
            sem_wait(&writeMutex);
        }
        sem_post(&mutex);
        printf("Reader %d is reading: %d\n", readerID, sharedResource);
        sem_wait(&mutex);
        readerCount--;
        if (readerCount == 0) 
		{
            sem_post(&writeMutex);
        }
        sem_post(&mutex);
        usleep(rand() % 1000000);
    }
    pthread_exit(NULL);
}
void* writerFunction(void* threadID) 
{
    int writerID = *((int*)threadID);

    for (int i = 0; i < 3; i++) 
	{
        sem_wait(&writeMutex); 
        sharedResource++;
        printf("Writer %d is writing: %d\n", writerID, sharedResource);
        sem_post(&writeMutex); 
        usleep(rand() % 1000000);
    }
    pthread_exit(NULL);
}

