#include <iostream>
#include <cstring>
#include <cstdlib>

char buf[128];
char* auth = nullptr;
char* service = nullptr;

int main() 
{
    if (!fgets(buf, sizeof(buf), stdin))
    {
        return (1); 
    }

    if (strncmp(buf, "auth ", 5) == 0)
    {
        auth = (char*)malloc(4);
        *auth = 0;

        char* input = buf + 5;
        if (strlen(input) <= 30)
        {
            strcpy(auth, input);
        }
    }

    if (strncmp(buf, "reset", 5) == 0)
    {
        free(auth);
        auth = nullptr;
    }

    if (strncmp(buf, "service", 7) == 0)
    {
        char temp[121];
        strncpy(temp, buf + 8, sizeof(temp) - 1);
        temp[sizeof(temp) - 1] = '\0';

        service = strdup(temp);
    }

    if (strncmp(buf, "login", 5) == 0)
    { 
        if (auth != nullptr && auth[32] != 0)
        {
            system("/bin/sh");
        }
        else 
        {
            std::cout << "Password:\n";
        }
    }

    return (0);
}