#include <stdio.h>
#include <string.h>
#include <unistd.h>

char* p(char* arg1, char* arg2)
{
    puts(arg2);

    char buf[4096];

    read(0, &buf, 4096);

    *strchr(&buf, 10) = 0;

    return strncpy(arg1, &buf, 20);
}

char* pp(char* arg1)
{
    char var_34[20];
    char var_20[28];

    p(&var_34, " - ");

    p(&var_20, " - ");

    strcpy(arg1, &var_34);

    int i = 4294967295U;

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

    *(edi - 1) = 32;

    return strcat(arg1, &var_20);
}

int main(int argc, char** argv, char** envp)
{
    char str[42];

    pp(&str);

    puts(&str);

    return (0);
}
