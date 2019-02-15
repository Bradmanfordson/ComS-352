#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

extern void *world();
extern void *hello();
extern void *exclamation();

int main(int argc, char *argv[])
{
    pthread_t helloID;
    pthread_t worldID;
    pthread_t exclamID;

    pthread_create(&helloID, NULL, hello, NULL);
    pthread_create(&worldID, NULL, world, NULL);
    pthread_create(&exclamID, NULL, exclamation, NULL);
    pthread_join(helloID, NULL);
    pthread_join(worldID, NULL);
    pthread_join(exclamID, NULL);

    // world();
    // hello();
    // exclamation();
    printf("\n");

    return 0;
}

void *world()
{
    printf(" world");
    return NULL;
}

void *hello()
{
    printf("Hello");
    return NULL;
}

void *exclamation()
{
    printf("!");
    return NULL;
}
// int world(void)
// {
//     printf(" world");
//     return 0;
// }

// int hello(void)
// {
//     printf("hello ");
//     return NULL;
// }

// int exclamation(void)
// {
//     printf("!");
//     return 0;
// }