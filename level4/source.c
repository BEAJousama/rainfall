#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int m = 0;

int print_input(char* input) {
    return printf(input);
}

// This function reads user input and performs a check on the global variable 'm'
int check_and_run() {
    char buffer[512];

    fgets(buffer, sizeof(buffer), stdin);

    print_input(buffer);

    int current_m = m;

    if (current_m != 16930116) 
    {
        return current_m;
    }

    return system("/bin/cat /home/user/level5/.pass");
}

int main(int argc, char** argv, char** envp) {
    return check_and_run();
}
