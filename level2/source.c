#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char* p()
{
    char input[80];

    fflush(stdout);
    gets(input);

    void* return_address = builtin_return_address(0);
    if (((unsigned long)return_address & 0xB0000000) != 0xB0000000) 
    {
        puts(input);
        return strdup(input);
    }

    printf("(%p)\n", return_address);
    exit(1);
}

int main(int argc, char** argv, char** envp) 
{
    return (int)p();
}
