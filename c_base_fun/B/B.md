##  `bsearch`

使用二分查找，查找一个被排序过的数组

依赖头文件
       `#include <stdlib.h>`

```c
   void *bsearch(const void *key, const void *base,
                 size_t nmemb, size_t size,
                 int (*compar)(const void *, const void *));
```

描述

```bash
key : 指向要查找的元素
base : 指向被查找的数组
nmemb : 被查找数组的大小
size : 被查找数组元素的大小
int (*compar)(const void *, const void *) ： 比对的函数
```

RETURN VALUE
       查找到了就返回对应的元素，查找不到就返回`NULL`

       ┌──────────┬───────────────┬─────────┐
       │Interface │ Attribute     │ Value   │
       ├──────────┼───────────────┼─────────┤
       │bsearch() │ Thread safety │ MT-Safe │
       └──────────┴───────────────┴─────────┘

使用示例：

```c
   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>

   struct mi {
       int nr;
       char *name;
   } months[] = {
       { 1, "jan" }, { 2, "feb" }, { 3, "mar" }, { 4, "apr" },
       { 5, "may" }, { 6, "jun" }, { 7, "jul" }, { 8, "aug" },
       { 9, "sep" }, {10, "oct" }, {11, "nov" }, {12, "dec" }
   };

   #define nr_of_months (sizeof(months)/sizeof(months[0]))

   static int
   compmi(const void *m1, const void *m2)
   {
       struct mi *mi1 = (struct mi *) m1;
       struct mi *mi2 = (struct mi *) m2;
       return strcmp(mi1->name, mi2->name);
   }

   int
   main(int argc, char **argv)
   {
       int i;

       qsort(months, nr_of_months, sizeof(struct mi), compmi);
       for (i = 1; i < argc; i++) {
           struct mi key, *res;
           key.name = argv[i];
           res = bsearch(&key, months, nr_of_months,
                         sizeof(struct mi), compmi);
           if (res == NULL)
               printf("'%s': unknown month\n", argv[i]);
           else
               printf("%s: month #%d\n", res->name, res->nr);c
       }
       exit(EXIT_SUCCESS);
   }
```





