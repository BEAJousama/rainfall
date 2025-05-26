#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int m = 0;

int v() 
{
    char buffer[512];

    fgets(buffer, sizeof(buffer), stdin);

    printf(buffer);

    int m_1 = m;
    if (m_1 != 60)
    {
        return m_1;
    }

    fwrite("Wait what?!\n", 1, 12, stdout);
    
    return system("/bin/sh");
}

int main(int argc, char** argv, char** envp) 
{
    return v();
}