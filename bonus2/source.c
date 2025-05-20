#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int language = 0;  // Global language flag: 0 = English, 1 = Finnish, 2 = Dutch

int greet_user(const char* name) {
    char greeting[100] = {0};

    if (language == 1) {
        // "Hyvää päivää " in UTF-8 encoded as raw bytes
        memcpy(greeting, "\x48\x79\x76\xc3\xa4\xc3\xa4\x20\x70\xc3\xa4\x69\x76\xc3\xa4\xc3\xa4\x20", 0x12);
    } else if (language == 2) {
        strcpy(greeting, "Goedemiddag! ");
    } else {
        strncpy(greeting, "Hello ", 7);
    }

    // Append the name provided by the user
    strcat(greeting, name);

    // Print the final greeting
    return puts(greeting);
}

int main(int argc, char** argv) {
    if (argc != 3) {
        return 1;
    }

    char buffer_name[0x4c] = {0};  // 76 bytes
    char name[0x21] = {0};         // 33 bytes

    // Copy first argument into buffer_name safely (max 40 chars)
    strncpy(buffer_name, argv[1], 0x28);  // 40 bytes
    // Copy second argument into name safely (max 32 chars)
    strncpy(name, argv[2], 0x20);         // 32 bytes

    // Detect language from environment
    const char* lang_env = getenv("LANG");
    if (lang_env != NULL) {
        if (memcmp(lang_env, "fi", 2) == 0) {
            language = 1;  // Finnish
        } else if (memcmp(lang_env, "nl", 2) == 0) {
            language = 2;  // Dutch
        }
        // Default is English (language = 0)
    }

    // Pass the name to greet_user
    return greet_user(name);
}
