#include <iostream>
#include <cstring>
#include <unistd.h>

char* p(char* arg1, const char* prompt) {
    std::cout << prompt;
    char buf[0x1008];  // 4104 bytes on stack

    // Read input into large stack buffer
    read(0, buf, 0x1000); // 4096 bytes

    // Replace newline with null
    char* newline = strchr(buf, '\n');
    if (newline)
        *newline = '\0';

    // Copy only first 20 bytes to arg1
    return strncpy(arg1, buf, 0x14); // 0x14 = 20
}

char* pp(char* arg1) {
    char var_34[0x14];  // 20 bytes
    p(var_34, " - ");

    char var_20[0x14];  // 20 bytes
    p(var_20, " - ");

    // Copy var_34 into arg1
    strcpy(arg1, var_34);

    // Find end of string and add space
    int i = -1;
    char* edi = arg1;
    while (++i < 0x1000 && *edi) edi++;
    *edi = ' ';
    edi[1] = '\0';

    // Append var_20 after space
    return strcat(arg1, var_20);
}

int main(int argc, char** argv, char** envp) {
    char str[0x2a]; // 42 bytes
    pp(str);
    puts(str);
    return 0;
}