# G开头的函数

> 文件操作相关的函数都放到`linux`系统编程中进行更新

```c
 #include <ctype.h>

int isalnum(int c);
int isalpha(int c);
int iscntrl(int c);
int isdigit(int c);
int isgraph(int c);
int islower(int c);
int isprint(int c);
int ispunct(int c);
int isspace(int c);
int isupper(int c);
int isxdigit(int c);

int isascii(int c);
int isblank(int c);

int isalnum_l(int c, locale_t locale);
int isalpha_l(int c, locale_t locale);
int isblank_l(int c, locale_t locale);
int iscntrl_l(int c, locale_t locale);
int isdigit_l(int c, locale_t locale);
int isgraph_l(int c, locale_t locale);
int islower_l(int c, locale_t locale);
int isprint_l(int c, locale_t locale);
int ispunct_l(int c, locale_t locale);
int isspace_l(int c, locale_t locale);
int isupper_l(int c, locale_t locale);
int isxdigit_l(int c, locale_t locale);
```

```bash
 isalnum()
        checks for an alphanumeric character; it is equivalent to (isalpha(c) || isdigit(c)).

isalpha()
        checks  for an alphabetic character; in the standard "C" locale, it is equivalent to (isupper(c) ||
        islower(c)).  In some locales, there may be additional characters for which isalpha() is  true—let‐
        ters which are neither uppercase nor lowercase.

isascii()
        checks whether c is a 7-bit unsigned char value that fits into the ASCII character set.

isblank()
        checks for a blank character; that is, a space or a tab.

iscntrl()
        checks for a control character.

isdigit()
        checks for a digit (0 through 9).

isgraph()
        checks for any printable character except space.

islower()
        checks for a lowercase character.

isprint()
        checks for any printable character including space.

ispunct()
        checks for any printable character which is not a space or an alphanumeric character.

isspace()
        checks  for  white-space  characters.   In the "C" and "POSIX" locales, these are: space, form-feed
        ('\f'), newline ('\n'), carriage return ('\r'), horizontal tab ('\t'), and vertical tab ('\v').

isupper()
        checks for an uppercase letter.

isxdigit()
        checks for hexadecimal digits, that is, one of
        0 1 2 3 4 5 6 7 8 9 a b c d e f A B C D E F.
```

