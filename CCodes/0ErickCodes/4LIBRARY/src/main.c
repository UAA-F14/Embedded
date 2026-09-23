#include "gpio.h"
#include <unistd.h>

#define LED 4
#define BUTTON1 5
#define BUTTON2 6
int main(void){
    gpio_init();
    gpio_configure(LED,GPIO_OUTPUT);
    gpio_configure(BUTTON1,GPIO_INPUT_PULLUP);
    gpio_configure(BUTTON2,GPIO_INPUT_PULLUP);
    gpio_start();
    while(1){
        if(gpio_get(BUTTON1)==0){
            gpio_set(LED,1);
            usleep(50000);
            gpio_set(LED,0);
            usleep(50000);
        }
        if(gpio_get(BUTTON2)==0){
            gpio_set(LED,1);
            usleep(500000);
            gpio_set(LED,0);
            usleep(500000);
        }
    }
    gpio_cleanup();
    return 0;
}