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