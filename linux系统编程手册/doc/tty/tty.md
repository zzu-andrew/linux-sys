[TOC]

## 终端

**获取和修改终端属性**

- 函数tcgetattr和函数tcsetattr可以用来获取和修改终端的属性

```c
       #include <termios.h>
       #include <unistd.h>

       int tcgetattr(int fd, struct termios *termios_p);

       int tcsetattr(int fd, int optional_actions,
                     const struct termios *termios_p);

       int tcsendbreak(int fd, int duration);

       int tcdrain(int fd);

       int tcflush(int fd, int queue_selector);

       int tcflow(int fd, int action);

       void cfmakeraw(struct termios *termios_p);

       speed_t cfgetispeed(const struct termios *termios_p);

       speed_t cfgetospeed(const struct termios *termios_p);

       int cfsetispeed(struct termios *termios_p, speed_t speed);

       int cfsetospeed(struct termios *termios_p, speed_t speed);

       int cfsetspeed(struct termios *termios_p, speed_t speed);

```

