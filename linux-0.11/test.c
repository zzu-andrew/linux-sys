#include <stdio.h>
#include <string.h>
#include <stddef.h>


struct info {
	long ___math_ret;
	long ___orig_eip;
	long ___edi;
	long ___esi;
	long ___ebp;
	long ___sys_call_ret;
	long ___eax;
	long ___ebx;
	long ___ecx;
	long ___edx;
	long ___orig_eax;
	long ___fs;
	long ___es;
	long ___ds;
	long ___eip;
	long ___cs;
	long ___eflags;
	long ___esp;
	long ___ss;
};





int main(int argc, char const *argv[])
{
    /* code */
    int x = 0;
    x  = offsetof(struct info,___eax),
    printf("x = [%d]\n", x);
    return 0;
}





