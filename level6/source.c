#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int n()
{
    return system("/bin/cat /home/user/level7/.pass");
}

int m()
{
    return puts("Nope");
}

int main(int argc, char** argv, char** envp) 
{
    char* user_input = malloc(64);

    int (**function_ptr)() = malloc(sizeof(void*));

    *function_ptr = m;

    strcpy(user_input, argv[1]);

    return (*function_ptr)();
}
