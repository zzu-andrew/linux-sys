#include <stdio.h>


void _color_led_on(void);



void led_on(void) __attribute__((weak, alias("_color_led_on")));



int main(int argc, char * argv[])
{

    led_on();

    return 0;
}





void _color_led_on(void)
{
    printf("Led on\n\n");
}










