#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <math.h>

typedef struct
{
    int hist[25];
    sem_t semaphore;
} Data;

void printHistogram(int hist[]);
void *create_shared_memory(size_t size);
void do_calculation(Data *data, int size);

int main(int argc, char const *argv[])
{

    int samples[4] = {5000, 50000, 100000, 10000000};
    for (int k = 0; k < sizeof(samples) / sizeof(int); k++)
    {
        int sample = samples[k];
        printf("sample is %d\n", sample);
        srand(time(NULL));

        // create shared memory
        void *shmem = create_shared_memory(sizeof(Data));
        Data *data = malloc(sizeof(Data));
        // second argument specify that semaphore is used for multiple process or multiple thread.
        // since we use semaphore for multiple process, second argument most be one.
        // if we use semaphore for multiple thread, this should be zero
        // third arument is the initial value for semaphore. (one for here)
        sem_init(&(data->semaphore), 1, 1);

        memcpy(shmem, data, sizeof(Data));

        clock_t begin = clock();

        // create some process for sampling
        int num_of_processes = 5;
        data = (Data *)shmem;

        for (int i = 0; i < num_of_processes; i++)
        {
            pid_t pid;
            if ((pid = fork()) == 0)
            {
                do_calculation(data, sample / num_of_processes);
                exit(0);
            }
        }

        // parent process
        for (int i = 0; i < num_of_processes; i++)
        {
            wait(NULL);
        }

        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("execution time of %d sample: %f\n", sample, time_spent);

        // printHistogram(data->hist);
        // printf("---------------------\n");
    }

    return 0;
}

void printHistogram(int hist[])
{
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < hist[i]; j++)
        {
            printf("*");
        }
        printf("\n");
    }
}

void *create_shared_memory(size_t size)
{
    // Our memory buffer will be readable and writable:
    int protection = PROT_READ | PROT_WRITE;

    // The buffer will be shared (meaning other processes can access it), but
    // anonymous (meaning third-party processes cannot obtain an address for it),
    // so only this process and its children will be able to use it:
    int visibility = MAP_SHARED | MAP_ANONYMOUS;

    // The remaining parameters to `mmap()` are not important for this use case,
    // but the manpage for `mmap` explains their purpose.
    return mmap(NULL, size * sizeof(int), protection, visibility, -1, 0);
    // char *tab = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED , -1, 0);
    // return tab;
}

void do_calculation(Data *data, int size)
{

    for (int i = 0; i < size; i++)
    {
        int counter = 0;
        for (int j = 0; j < 12; j++)
        {
            int random = rand() % 101;
            if (random >= 49)
            {
                counter++;
            }
            else
            {
                counter--;
            }
        }
        sem_wait(&(data->semaphore));
        (data->hist[counter + 12])++;
        sem_post(&(data->semaphore));
    }
}