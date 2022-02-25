#include <pthread.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define N 5

sem_t chopstic[N];

void *philosopher(void *args);
int main()
{

    pthread_t threads[N];

    for (int i = 0; i < N; i++)
        sem_init(&chopstic[i], 0, 1);

    for (int i = 0; i < N; i++)
    {
        // create philosopher processes
        int *phnum = malloc(sizeof(int *));
        *phnum = i;
        pthread_create(&threads[i], NULL, philosopher, phnum);
    }

    for (int i = 0; i < N; i++)
    {
        pthread_join(threads[i], NULL);
    }
}

void *philosopher(void *args)
{
    int *philosopher_num = (int *)args;
    int i = *philosopher_num;
    while (1)
    {
        printf("philosopher %d is hungry...\n", i + 1);
        // if philosopher number is even, first take the left chopstic then take the right one
        // and vice versa for philosopher that has odd number
        // this approach is used to prevent starvation situation
        if (i % 2 == 0)
        {
            sem_wait(&chopstic[i]);
            sem_wait(&chopstic[(i + 1) % N]);
        }
        else
        {
            sem_wait(&chopstic[(i + 1) % N]);
            sem_wait(&chopstic[i]);
        }

        // printing that philosopher is eating the nodle...
        printf("philosopher %d is eating with %d and %d chopstic...\n", i + 1, i + 1, (i + 1) % N + 1);
        sleep(1);

        // thinking
        printf("philosopher %d is thinking...\n", i + 1);
        if (i % 2 == 0)
        {
            sem_post(&chopstic[i]);
            sem_post(&chopstic[(i + 1) % N]);
        }
        else
        {
            sem_post(&chopstic[(i + 1) % N]);
            sem_post(&chopstic[i]);
        }

        sleep(2);

        // break;
    }
}
