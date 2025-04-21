#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char* p() {
    char input[80]; // buffer on the stack

    fflush(stdout); // flush output to make sure prompt shows
    gets(input);    // unsafe function, vulnerable to buffer overflow!

    // Check if the return address is in user space
    void* return_address = builtin_return_address(0);
    if (((unsigned long)return_address & 0xB0000000) != 0xB0000000) 
    {
        // If return address is safe, print input and return a copy of it
        puts(input);
        return strdup(input); // duplicate the input string
    }

    // Otherwise, print the suspicious return address and exit
    printf("(%p)\n", return_address);
    exit(1); // immediate exit, doesn't return
}

int main(int argc, char** argv, char** envp) {
    return (int)p(); // call function p and return its result (casted to int)
}
