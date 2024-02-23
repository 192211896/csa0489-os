#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
int sharedResource = 0;
pthread_mutex_t mutex;
void* threadFunction(void* threadID) 
{
    int threadNum = *((int*)threadID);
    for (int i = 0; i < 5; i++) 
	{
        pthread_mutex_lock(&mutex);
        sharedResource++;
        printf("Thread %d modified the shared resource: %d\n", threadNum, sharedResource);
        pthread_mutex_unlock(&mutex);
        int usleep(rand() % 1000000);
    }
    pthread_exit(NULL);
}
int main() 
{
    pthread_mutex_init(&mutex, NULL);
    pthread_t thread1, thread2;
    int id1 = 1, id2 = 2;
    pthread_create(&thread1, NULL, threadFunction, (void*)&id1);
    pthread_create(&thread2, NULL, threadFunction, (void*)&id2);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_mutex_destroy(&mutex);
    return 0;
}

