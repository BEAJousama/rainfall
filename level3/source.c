#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int m = 0;  // Declare and initialize global variable 'm'

int v() 
{
    char buffer[512];  // A buffer to hold the input string (512 bytes)

    // Read a line of input from stdin into the buffer (max 512 bytes)
    fgets(buffer, sizeof(buffer), stdin);

    // Print the content of the buffer
    printf("%s", buffer);

    // Check if the value of the variable 'm' is 0x40 (64 in decimal)
    int m_1 = m;
    if (m_1 != 64) {
        // If 'm' is not 0x40, return the value of m_1
        return m_1;
    }

    // If 'm' is 0x40, print the message and execute /bin/sh
    fwrite("Wait what?!\n", 1, 12, stdout);  // Prints "Wait what?!"
    
    // Execute a shell (/bin/sh) and return the status of that execution
    return system("/bin/sh");
}

int main(int argc, char** argv, char** envp) 
{
    return v();
}