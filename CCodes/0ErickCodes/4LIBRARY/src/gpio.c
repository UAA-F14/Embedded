#include "gpio.h"
#include <stdio.h>
#include <gpiod.h>

static struct gpiod_chip *chip;
static struct gpio_line_request *request;
static struct gpio_line_config *config;


int gpio_init(void){

    chip=gpiod_chip_open("/dev/gpiochip0");

    if(chip==NULL){
        perror("error al abrir GPIO chip")
        return 1;
    }
    config=

}
int gpio_configure(unsigned int gpio,int mode){
    struct gpiod_line_settings *settings;

    settings=gpio_line_settings_new();
    if(settings==NULL){
        return 1;
    }
    switch(mode){
        case GPIO_INPUT:
        gpio_line_settings_set_direction();
    }
}
int gpio_start(void);
int gpio_set(unsigned int gpio, int value);
int gpio_get(unsigned int gpio);
void gpio_cleanup(void);