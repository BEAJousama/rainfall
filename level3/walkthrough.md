```
Start GDB:

gdb ./level2
Set a breakpoint at the function v() where the value of m is checked:

(gdb) break v
```

```
    Run the program in GDB:

    (gdb) run
```

```
    Change the value of m at the point where the breakpoint hits:

    (gdb) set variable m = 64
```

```
    Continue execution:
    (gdb) continue
```


cat /home/user/level4/.pass