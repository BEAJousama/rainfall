#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    if (argc < 2 || atoi(argv[1]) != 423)
    {
        fprintf(stderr, "No !\n");
    } 
    else 
    {
        char* args[] = {"/bin/sh", NULL};
        
        gid_t gid = getegid();
        uid_t uid = geteuid();
        
        setresgid(gid, gid, gid);
        setresuid(uid, uid, uid);
        
        execv("/bin/sh", args);
    }
    return 0;
}
