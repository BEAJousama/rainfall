#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void o()
{
    system("/bin/sh");
    exit(1);
}

void n()
{
    char buffer[512];

    fgets(buffer, sizeof(buffer), stdin);

    printf(buffer);

    exit(1);
}

int main(int argc, char** argv, char** envp)
{
    n();
}
