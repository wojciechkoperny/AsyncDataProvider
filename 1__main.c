#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#ifndef NULL_PTR
   #define NULL_PTR     ((void *)0u)
#endif
static pthread_t thread_fun1, thread_fun2;

void SigintHandler(int a)
{
    printf("BYE World : TERMINATION : %d\n ",a);
    (void)pthread_cancel(thread_fun1);
    (void)pthread_cancel(thread_fun2);
}

void* fun1 (void *arg)
{
    static int ilosc=0;
    while(1)
    {
        printf ("\e[1;32mThis is cmake test %d\e[0m\n", ilosc);
        ilosc++;
        sleep(1);
    }
}
void* fun2 (void *arg)
{
    static int ilosc=0;
    while(1)
    {
        printf ("\e[1;33mOther Task %d\e[0m\n", ilosc);
        ilosc++;
        sleep(2);
    }
}
int main(int argc, char *argv[])
{
    printf("Hello World\n");

    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = SigintHandler;

    (void)sigaction(SIGINT, &sa, NULL);

    (void)pthread_create(&thread_fun1, NULL_PTR, &fun1, NULL_PTR);
    (void)pthread_create(&thread_fun2, NULL_PTR, &fun2, NULL_PTR);

    (void)pthread_join(thread_fun1, NULL_PTR);
    (void)pthread_join(thread_fun2, NULL_PTR);


    return 0;
}
