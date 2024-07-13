#include <unistd.h>
#include <stdio.h>

int main()
{
    uid_t uid = getuid();
    uid_t euid = geteuid();
    printf("User Id is %d, effective User Id is: %d \n", uid, euid);
    return 0;
}