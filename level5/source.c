#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void spawn_shell_and_exit()
{
    system("/bin/sh");
    exit(1);
}


void read_input_and_print()
{
    char buffer[512];

    fgets(buffer, sizeof(buffer), stdin);

    printf("%s", buffer);

    exit(1);
}

int main(int argc, char** argv, char** envp)
{
    read_input_and_print();
}
