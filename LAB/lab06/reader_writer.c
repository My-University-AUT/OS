#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>

#ifndef __cplusplus
typedef unsigned char bool;
static const bool false = 0;
static const bool true = 1;
#endif

typedef struct
{
    int counter;
    int read_count;
    int max_count;
    sem_t mutex;
    sem_t write_access;
} Data;

void *create_shared_memory(size_t size);

// sem_t mutex;
// sem_t write_access;

void writer(Data *data);
void reader(Data *data);
int main(int argc, char const *argv[])
{

    // create shared memory
    void *shmem = create_shared_memory(sizeof(Data));
    Data *data = malloc(sizeof(Data));
    data->counter = 0;
    data->read_count = 0;
    data->max_count = 5;
    // second argument specify that semaphore is used for multiple process or multiple thread.
    // since we use semaphore for multiple process, second argument most be one.
    // if we use semaphore for multiple thread, this should be zero
    // third arument is the initial value for semaphore. (one for here)
    sem_init(&(data->mutex), 1, 1);
    sem_init(&(data->write_access), 1, 1);

    memcpy(shmem, data, sizeof(Data));

    data = (Data *)shmem;

    pid_t pid;
    if ((pid = fork()) == 0)
    {
        writer(data);
        exit(0);
    }

    int num_of_reader_processes = 3;
    for (int i = 0; i < num_of_reader_processes; i++)
    {
        if ((pid = fork()) == 0)
        { // child process
            reader(data);
            exit(0);
        }
    }

    // parent process
    for (int i = 0; i < num_of_reader_processes+1; i++)
    {
        wait(NULL);
    }

    return 0;
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

void writer(Data *data)
{
    pid_t pid = getpid();
    while (true)
    {
        sem_wait(&(data->write_access));
        bool done = false;
        if (data->counter >= data->max_count)
        {
            done = true;
        }
        else
        {
            (data->counter)++;
            printf("writing to  counter: %d pid: %d\n", data->counter, pid);
        }

        sem_post(&(data->write_access));
        sleep(.25);

        if (done)
        {
            break;
        }
    }
}
void reader(Data *data)
{
    pid_t pid = getpid();

    while (true)
    {

        sem_wait(&(data->mutex));
        (data->read_count)++; // on each entry of reader increment readcount
        if (data->read_count == 1)
        {
            sem_wait(&(data->write_access));
        }
        sem_post(&(data->mutex));

        printf("reading counter: %d pid:%d\n", data->counter, pid);
        bool done = false;
        if (data->counter >= data->max_count)
        {
            done = true;
        }

        sem_wait(&(data->mutex));
        (data->read_count)--; // on every exit of reader decrement readcount
        if (data->read_count == 0)
        {
            sem_post(&(data->write_access));
        }
        sem_post(&(data->mutex));
        sleep(.7);
        if (done)
        {
            break;
        }
    }
}