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

int main(int argc, char** argv, char** envp) {
    // Allocate 64 bytes for user input
    char* user_input = malloc(64);

    // Allocate memory for a function pointer
    int (**function_ptr)() = malloc(sizeof(void*));

    // Initialize the function pointer to point to 'm'
    *function_ptr = m;

    // Copy user input into the buffer without bounds checking (vulnerable!)
    strcpy(user_input, argv[1]);

    // Call the function through the function pointer
    return (*function_ptr)();
}
