#

# Q开头的函数



排序数组函数

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int
    cmpstringp(const void *p1, const void *p2)
{
    /* The actual arguments to this function are "pointers to
              pointers to char", but strcmp(3) arguments are "pointers
              to char", hence the following cast plus dereference */

    return strcmp(* (char * const *) p1, * (char * const *) p2);
}

int
    main(int argc, char *argv[])
{
    int j;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <string>...\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    qsort(&argv[1], argc - 1, sizeof(char *), cmpstringp);

    for (j = 1; j < argc; j++)
        puts(argv[j]);
    exit(EXIT_SUCCESS);
}
```





