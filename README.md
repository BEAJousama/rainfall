# Rainfall

**Rainfall** is a 42 school CTF (Capture The Flag) project focused on binary exploitation. Players progress through 14 levels (level0–level9, bonus0–bonus3), each presenting a vulnerable 32-bit ELF binary running on a remote machine. The goal of each level is to exploit the binary to read the password of the next level's user, and ultimately reach the `end` user.

## Setup

Connect to the machine via SSH:

```sh
export RAINFALL_IP=<machine_ip>
ssh level0@${RAINFALL_IP} -p 4242
# password: level0
```

Each level's home directory contains a SUID binary owned by the next user. Exploiting it grants the privileges needed to read the next password.

## Project Structure

Each level directory contains:

| File | Description |
|------|-------------|
| `source.c` | Reconstructed/decompiled C source of the binary |
| `walkthrough.md` | Step-by-step explanation of the exploit |
| `flag` | The password for the next level |

## Levels Overview

### level0 — Magic Number Check

The binary expects a specific integer argument (`423`). Passing it spawns a shell with `level1`'s privileges.

**Technique:** Hardcoded value bypass.

---

### level1 — Stack Buffer Overflow (ret2win)

The binary reads user input using `gets()` into a fixed-size buffer, with no bounds checking. A hidden `run()` function calls `system("/bin/sh")`. Overflowing the buffer allows overwriting the saved return address to redirect execution to `run()`.

**Technique:** Stack buffer overflow, return address overwrite.

---

### level2 — Heap Shellcode Injection

`gets()` overflows a stack buffer. A return-address check prevents pointing back into the stack region (`0xBxxxxxxx`). Instead, shellcode is injected into heap memory (via `strdup`) and the return address is overwritten with the heap address.

**Technique:** Stack buffer overflow, heap shellcode injection.

---

### level3 — Format String (Write to Global Variable)

`printf(buffer)` is called with user input directly as the format string. The global variable `m` must equal `60` to spawn a shell. `%n` is used to write the value `60` to the address of `m`.

**Technique:** Format string vulnerability, arbitrary write with `%n`.

---

### level4 — Format String (Write Specific Value)

Similar to level3 but the global variable `m` must equal `16930116` (0x1030604). A padded `%n` format string writes this exact value to `m`, causing the program to print the next level's password.

**Technique:** Format string vulnerability, large value write with `%n`.

---

### level5 — Format String + GOT Overwrite

`printf(buffer)` is vulnerable. A hidden function `o()` calls `system("/bin/sh")`. The address of `exit()` in the GOT is overwritten with the address of `o()` using a format string exploit, so when `exit(1)` is called, it jumps to `o()` instead.

**Technique:** Format string vulnerability, GOT (Global Offset Table) overwrite.

---

### level6 — Heap Buffer Overflow (Function Pointer Overwrite)

Two heap allocations are made back-to-back: a 64-byte input buffer and a 4-byte function pointer. The function pointer initially points to `m()` ("Nope"). Overflowing the input buffer with `strcpy(argv[1])` overwrites the function pointer with the address of `n()`, which prints the next password.

**Technique:** Heap buffer overflow, function pointer overwrite.

---

### level7 — Double Heap Overflow + GOT Overwrite

Two pairs of heap-allocated structs each hold a data pointer. By overflowing the first struct's data pointer into the second struct's pointer field, the second `strcpy` writes to an arbitrary address. This is used to overwrite the `puts` GOT entry with `m()`, which prints the password read by `fopen`.

**Technique:** Double heap overflow, GOT overwrite.

---

### level8 — Use-After-Free / Heap Exploitation

An interactive program handles `auth`, `reset`, and `service` commands. `auth` allocates 4 bytes; `service` uses `strdup`. Due to `malloc`'s reuse behavior, allocating `service` after `reset` (freeing `auth`) can place data at the same address. Issuing `login` then accesses the freed/reused memory to pass an authentication check.

**Technique:** Use-after-free, heap memory reuse.

---

### level9 — C++ Vtable Overwrite

A C++ class `N` stores a vtable pointer at offset 0 and user-controlled data starting at offset 4. `setAnnotation()` uses `memcpy(this + 4, input, strlen(input))` with no length check. Overflowing object `a`'s buffer overwrites object `b`'s vtable pointer. When a virtual method is called on `b`, it dispatches through the attacker-controlled pointer, redirecting execution to shellcode placed in `a`'s buffer.

**Technique:** Heap buffer overflow, C++ vtable overwrite.

---

### bonus0 — Stack Buffer Overflow via strncpy Chain

`p()` reads up to 4096 bytes but copies only 20 bytes into a caller-supplied buffer using `strncpy`. Two such reads are chained with `strcpy` to concatenate them into a final buffer. Since `strncpy` does not null-terminate when the source is longer than the limit, the concatenated result overflows the stack frame, overwriting the return address with a shellcode address.

**Technique:** Stack buffer overflow, `strncpy` non-null-termination, shellcode injection.

---

### bonus1 — Integer Overflow (atoi / memcpy)

The program takes `atoi(argv[1])` as a length and rejects values greater than 9. However, a large negative number bypasses this check (e.g., `-2147418112`). When multiplied by 4 in `memcpy(buffer, argv[2], input_length * 4)`, the result wraps around to a small positive number via unsigned integer overflow. Meanwhile, the stored `input_length` value matches `0x574F4C46`, triggering `execl("/bin/sh")`.

**Technique:** Integer overflow, signed/unsigned conversion bypass.

---

### bonus2 — Environment Variable Buffer Overflow

The program copies `argv[1]` (up to 40 bytes) and `argv[2]` (up to 32 bytes) into a 76-byte buffer via `strncpy`. Based on the `LANG` environment variable, a greeting prefix is prepended. Setting `LANG=fi` adds an 18-byte Finnish prefix, pushing the total past the 100-byte `greeting` buffer boundary when `strcat` appends the name. The overflow overwrites the return address with a shellcode address placed in the environment.

**Technique:** Buffer overflow via environment variable, `strcat` overflow.

---

### bonus3 — Null Byte Injection

The program reads a password from `/home/user/end/.pass` and calls `password[atoi(argv[1])] = '\0'`. Passing `0` as the argument sets `password[0] = '\0'`, making the password an empty string. If `argv[1]` is also an empty string (or `"0"`), `strcmp(password, argv[1])` compares two empty strings and succeeds, spawning a shell.

**Technique:** Null byte injection, off-by-one, `strcmp` bypass.

---

## Exploitation Techniques Summary

| Level  | Technique |
|--------|-----------|
| level0 | Hardcoded value bypass |
| level1 | Stack buffer overflow, ret2win |
| level2 | Stack overflow, heap shellcode injection |
| level3 | Format string (`%n`), global variable write |
| level4 | Format string (`%n`), precise value write |
| level5 | Format string, GOT overwrite |
| level6 | Heap overflow, function pointer overwrite |
| level7 | Double heap overflow, GOT overwrite |
| level8 | Use-after-free, heap reuse |
| level9 | Heap overflow, C++ vtable overwrite |
| bonus0 | Stack overflow, `strncpy` non-termination |
| bonus1 | Integer overflow, signed/unsigned bypass |
| bonus2 | Environment variable overflow, `strcat` |
| bonus3 | Null byte injection, `strcmp` bypass |

## Resources

- [GDB — GNU Debugger](https://www.gnu.org/software/gdb/)
- [pwntools — CTF exploitation framework](https://github.com/Gallopsled/pwntools)
- [Exploit Education — Protostar / Phoenix](https://exploit.education/)
- [LiveOverflow Binary Exploitation playlist](https://www.youtube.com/playlist?list=PLhixgUqwRTjxglIswKp9mpkfPNfHkzyeN)
- [x86 Calling Convention](https://en.wikipedia.org/wiki/X86_calling_conventions)
