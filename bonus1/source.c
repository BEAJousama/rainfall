#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv, char** envp) 
{
    char buffer[40];
    int input_length = atoi(argv[1]);

    if (input_length > 9)
    {
        return 1;
    }


    memcpy(buffer, argv[2], input_length * 4);

    if (input_length == 0x574F4C46)
    {
        execl("/bin/sh", "sh", NULL);
    }

    return 0;
}
