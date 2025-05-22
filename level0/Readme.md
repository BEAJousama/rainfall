# RainFall: Level0 Walkthrough

## Step 1: Overview

We connect to the RainFall machine and authenticate as `level0`.

```bash
ssh level0@${RAINFALL_IP} -p 4242
```

In the home directory:

```bash
level0@RainFall:~$ ls -l
-rwsr-s---+ 1 level1 users 7552 Aug 30  2022 level0
```

The binary is owned by `level1` and has the SUID bit set, meaning if it executes any shell, it will run with `level1`'s privileges.

---

## Step 2: Binary Behavior

When we execute it:

```bash
level0@RainFall:~$ ./level0
No !
```

Disassembling or decompiling the binary reveals:

```c
int main(int argc, char* argv[]) {
    if (argc < 2 || atoi(argv[1]) != 423) {
        fprintf(stderr, "No !\n");
    } else {
        char* args[] = {"/bin/sh", NULL};

        gid_t gid = getegid();
        uid_t uid = geteuid();

        setresgid(gid, gid, gid);
        setresuid(uid, uid, uid);

        execv("/bin/sh", args);
    }
    return 0;
}
```

The binary checks if the first argument equals `423`. If true, it escalates privileges and spawns a shell.

---

## Step 3: Exploitation

We pass `423` as the argument:

```bash
level0@RainFall:~$ ./level0 423
$ whoami
level1
```

We now have a shell with `level1`'s privileges.

---

## Step 4: Retrieving the Flag

```bash
$ cat /home/user/level1/.pass
1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a
```

---

## Step 5: Move to Level01

```bash
level0@RainFall:~$ su level1
Password: 1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a
```
