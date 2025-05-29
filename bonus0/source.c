#include <stdio.h>
#include <string.h>
#include <unistd.h>

char* p(char* arg1, char* arg2)
{
    puts(arg2); //Prints arg2 (a prompt like " - ").

    char buf[4096];

    read(0, &buf, 4096); //Reads up to 4096 bytes from standard input (read(0, ...)) into a local buffer.

    *strchr(&buf, 10) = 0; //Replaces the first newline (\n) with \0 to null-terminate the string.

    return strncpy(arg1, &buf, 20); //Copies at most 20 bytes from input into arg1.
}

char* pp(char* arg1)
{
    char var_34[20];
    char var_20[20];

    p(&var_34, " - ");

    p(&var_20, " - ");

    strcpy(arg1, &var_34); //Copies the first input (var_34) into arg1 using strcpy.

    int i = 4294967295U;

    //Finds the end of the copied string (null terminator), using a loop.
    char* edi = arg1;
    while (i != 0)
    {
        bool cond = (*edi != 0);

        edi = &edi[1];

        i -= 1;

        if (!cond) 
        {
            break;
        }
    }

    //Overwrites the last character (the \0) with a space ' ':
    *(edi - 1) = ' ';

    //Concatenates the second input (var_20) using strcat.
    return strcat(arg1, &var_20);
}

int main(int argc, char** argv, char** envp)
{
    char str[42]; // result buffer

    pp(&str); // get two inputs and combine them into str

    puts(&str); // print the combined string

    return (0);
}
