#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main()
{
    void *mapped_page;

    while (1)
    {
        printf("Keeping the program running...\n");

        printf("Writing...\n");
        // Memory map an empty page
        mapped_page = mmap(0, getpagesize(), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if (mapped_page == MAP_FAILED)
        {
            perror("mmap failed");
            return 1;
        }

        printf("Writing Hello World...\n");
        strcpy((char *)mapped_page, "Hello, world!");

        sleep(4);
    }
}