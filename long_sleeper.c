#include <stdio.h>
#include <unistd.h>

int main()
{
    while (1)
    {
        printf("New sleep is running...\n");
        sleep(4);
    }
    return 0;
}