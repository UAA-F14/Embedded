#include <stdio.h>
#include <unistd.h>
#include <gpiod.h>

#define LED 4
#define BUTTON 6


int main(void){
    struct gpiod_chip *chip;
    struct gpiod_line_settings *led_settings;
    struct gpiod_line_settings *button_settings;

    struct gpiod_line_config *line_config;
    struct gpiod_line_request *request;


    unsigned int led = LED;
    unsigned int button = BUTTON;
    chip = gpiod_chip_open("/dev/gpiochip1");

    if(chip == NULL){
        perror("Error al abrir GPIO chip");
        return 1;
    }

    led_settings = gpiod_line_settings_new();


    if (led_settings == NULL)
    {
        perror("Error al crear LED settings");
        gpiod_chip_close(chip);
        return 1;
    }

    gpiod_line_settings_set_direction(led_settings, GPIOD_LINE_DIRECTION_OUTPUT);
    // ------- button --------
    button_settings = gpiod_line_settings_new();

    if (button_settings == NULL)
    {
        perror("Error al crear BUTTON settings");
        gpiod_line_settings_free(led_settings);
        gpiod_chip_close(chip);
        return 1;
    }

    gpiod_line_settings_set_direction(button_settings, GPIOD_LINE_DIRECTION_INPUT);
    gpiod_line_settings_set_bias(button_settings, GPIOD_LINE_BIAS_PULL_UP);

    line_config = gpiod_line_config_new();

    if (line_config == NULL)
    {
        perror("Error al crear line config");
        gpiod_line_settings_free(button_settings);
        gpiod_chip_close(chip);
        return 1;
    }

    if (gpiod_line_config_add_line_settings(line_config,&led,1,led_settings) < 0)
    {
        perror("Error al agregar GPIO");
        //gpiod_line_config_free(line_config);
        gpiod_line_settings_free(led_settings);
        gpiod_chip_close(chip);
        return 1;
    }
    
    if (gpiod_line_config_add_line_settings(line_config,&button,1,button_settings) < 0)
    {
        perror("Error al agregar GPIO");
        //gpiod_line_config_free(line_config);
        gpiod_line_settings_free(button_settings);
        gpiod_chip_close(chip);
        return 1;
    }

    request = gpiod_chip_request_lines(chip,NULL,line_config);

    if (request == NULL)
    {
        perror("Error al solicitar GPIO");
        //gpiod_line_config_free(line_config);
        gpiod_line_settings_free(button_settings);
        gpiod_chip_close(chip);
        return 1;

    }
    
while(1){
    enum gpiod_line_value value;
    value = gpiod_line_request_get_value(request, button);
    if(value == GPIOD_LINE_VALUE_ACTIVE){
        gpiod_line_request_set_value(request, led, GPIOD_LINE_VALUE_ACTIVE);
    } else {
        gpiod_line_request_set_value(request, led, GPIOD_LINE_VALUE_INACTIVE);
    }
    usleep(10000);
}
    
    return 0;

}
