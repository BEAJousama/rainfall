#include <stdio.h>
#include <stdlib.h>

int run() {
    printf("Good... Wait what?\n");
    return system("/bin/sh");
}

int main(int argc, char** argv, char** envp) {
    char buf[64];
    gets(buf);
    return (0);
}
