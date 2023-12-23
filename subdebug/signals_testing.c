

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void    signal_handler(int signum)
{
    printf("Caught signal %d, comign out...\n", signum);
    exit(1);
}

int main()
{
    signal(SIGINT, signal_handler);

    while (1)
    {
        printf("sleeping for a second\n");
        sleep(1);
    }
    return (0);
}