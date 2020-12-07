#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#ifndef NULL_PTR
#define NULL_PTR     ((void *)0u)
#endif
#define DEFAULT_TIMER 1U
#define DBUDOWANIETESTOWE
static pthread_t thread_fun1, thread_fun2;
int Timer = DEFAULT_TIMER;

void SigintHandler(int a)
{
    printf("\033[0;31m\nBYE World : TERMINATION : %d\n ",a);
    (void)pthread_cancel(thread_fun1);
    (void)pthread_cancel(thread_fun2);
}

void* fun1 (void *arg)
{
    static int ilosc=0;
    while(1)
    {
        printf ("\e[1;32mThis is TASK 1 call number: %d\e[0m\n", ilosc);
        ilosc++;     
        sleep(*((int*)arg));
    }
}
void* fun2 (void *arg)
{
    static int ilosc=0;
    while(1)
    {
        printf ("\e[1;33mThis is TASK 2 call number: %d\e[0m\n", ilosc);
        ilosc++;
        sleep(2);
    }
}


int main(int argc, char *argv[])
{
    if (argc >1)
    {
        Timer = atoi(argv[1]);
    } 
    printf("Hello World\n");

    #ifdef TEST_BUILD
        printf("\033[0;31mTEST_BUILD SET!\n");
    #endif

    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = SigintHandler;

    (void)sigaction(SIGINT, &sa, NULL);

    (void)pthread_create(&thread_fun1, NULL, &fun1, &Timer);
    (void)pthread_create(&thread_fun2, NULL, &fun2, NULL);

    (void)pthread_join(thread_fun1, NULL);
    (void)pthread_join(thread_fun2, NULL);


    return 0;
}
