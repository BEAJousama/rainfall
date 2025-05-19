#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // for execl

int main(int argc, char** argv, char** envp) {
    // Convert the first argument to an integer
    int input_length = atoi(argv[1]);

    // If the input is greater than 9, return error
    if (input_length > 9) {
        return 1;
    }

    // Declare a 60-byte buffer (assuming stack space or similar)
    char buffer[60];

    // Copy (input_length * 4) bytes from argv[2] into buffer
    memcpy(buffer, argv[2], input_length * 4);

    // Check if input_length equals 0x574F4C46 (this seems odd – likely a mistake).
    // More likely intended: check if first 4 bytes of buffer equal 'FLOW' (0x464C4F57).
    if (input_length == 0x574F4C46) {
        // If condition met, spawn a shell
        execl("/bin/sh", "sh", NULL);
    }

    return 0;
}
