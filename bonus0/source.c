#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Function 'p' takes two arguments: arg1 and arg2.
char* p(char* arg1, char* arg2)
{
    puts(arg2);

    char buf[4096];

    read(0, &buf, 4096);

    *strchr(&buf, 0xa) = 0;

    return strncpy(arg1, &buf, 20);
}

// Function 'pp' processes the input and builds a final string.
char* pp(char* arg1)
{
    char var_34[20];
    char var_20[20];

    p(&var_34, " - ");

    p(&var_20, " - ");

    strcpy(arg1, &var_34);

    int i = 0xFFFFFFFF;

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

    *(edi - 1) = 0x20;

    return strcat(arg1, &var_20);
}

int main(int argc, char** argv, char** envp)
{
    char str[42];

    pp(&str);

    puts(&str);

    return (0);
}
