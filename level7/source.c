#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char c[68];

int m()
{
    return printf("%s - %d\n", c, time(NULL));
}

int main(int argc, char** argv, char** envp)
{
    int* first = malloc(8);
    int* second = malloc(8);

    first[0] = 1;
    first[1] = (int)malloc(8);

    second[0] = 2;
    second[1] = (int)malloc(8);

    // Copy argv[1] into memory pointed to by first[1]
    strcpy((char*)first[1], argv[1]);

    // Copy argv[2] into memory pointed to by second[1]
    strcpy((char*)second[1], argv[2]);

    // Read a string from the secret file into 'c'
    FILE* secret = fopen("/home/user/level8/.pass", "r");
    if (secret != NULL) 
    {
        fgets(c, sizeof(c), secret);
        fclose(secret);
    } 
    else 
    {
        perror("Error opening secret file");
    }

    puts("~~");

    return (0);
}
