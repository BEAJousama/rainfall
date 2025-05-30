First of all we connect to the machine via ssh as described bellow

```
    export RINFALL_IP=10.11.100.172

    ssh level0@${RINFALL_IP} -p 4242
    password: level0
```

After we get in, we list the files in home directory

```
    level0@RainFall:~$ ls -la
    -rwsr-x---+ 1 level1 users  747441 Mar  6  2016 level0
```

The binary is owned by level1 and has the SUID bit set, meaning if it executes any shell, it will run with level1's privileges.

We try to execute the binary file to get an idea of what it does exactly

```
    level0@RainFall:~$ ./level0 
    Segmentation fault (core dumped)
    level0@RainFall:~$ ./level0 aaaa
    No !
    level0@RainFall:~$
```

We copy the binary to our host machine with scp command to be able to decompile it with ghidra

```
    scp -P 4242 level0@${RAINFALL_IP}:/home/users/level0/level0 . 
```
Here is the decompiled source code of the binary:

```
    int main(int argc, char* argv[])
    {
        if (argc < 2 || atoi(argv[1]) != 423)
        {
            fprintf(stderr, "No !\n");
        } 
        else 
        {
            char* args[] = {"/bin/sh", NULL};
            
            gid_t gid = getegid();
            uid_t uid = geteuid();
            
            setresgid(gid, gid, gid);
            setresuid(uid, uid, uid);
            
            execv("/bin/sh", args);
        }
        return 0;
    }
```

So if argv[1] is "423", we get a shell:

```
    level0@RainFall:~$ ./level0 423
    $ cat /home/user/level1/.pass    
    1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a
```

go to next level

```
level0@RainFall:~$ su level1
password:1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a
level1@RainFall:~$
```