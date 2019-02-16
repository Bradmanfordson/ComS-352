// Allen Bradley Roberts

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *world();
void *hello();
void *exclamation();

int main(int argc, char *argv[])
{

    pthread_t thread;

    pthread_create(&thread, NULL, world, NULL);
    pthread_join(thread, NULL);
    printf("\n");

    return 0;
}

void *world()
{
    pthread_t thread1;
    pthread_t thread2;

    pthread_create(&thread1, NULL, hello, NULL);
    pthread_join(thread1, NULL);

    printf("world");

    pthread_create(&thread2, NULL, exclamation, NULL);
    pthread_join(thread2, NULL);
}

void *hello()
{
    printf("Hello ");
}

void *exclamation()
{
    printf("!");
}
