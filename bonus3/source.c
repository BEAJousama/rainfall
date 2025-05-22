#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

int main(int argc, char** argv, char** envp) 
{
    FILE* fp = fopen("/home/user/end/.pass", "r");
    if (fp == NULL || argc != 2) {
        return -1;
    }

    char password[65];
    memset(password, 0, sizeof(password));

    fread(password, 1, 66, fp);

    int index = atoi(argv[1]);
    if (index >= 0 && index < sizeof(password))
    {
        password[index] = '\0';
    } 
    else
    {
        fclose(fp);
        return (-1);
    }

    char fallback[66];
    fread(fallback, 1, 65, fp);
    fclose(fp);

    if (strcmp(password, argv[1]) != 0)
    {
        puts(fallback);
    } 
    else 
    {
        execl("/bin/sh", "sh", NULL);
    }

    return (0);
}