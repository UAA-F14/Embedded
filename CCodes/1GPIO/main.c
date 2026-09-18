#include <stdio.h>
#include <unistd.h>
#include <gpiod.h>

int main(void){
    struct gpiod_chip *chip;
    struct gpiod_line_settings *settings;
    struct gpiod_line_config *line_config;
    struct gpiod_line_request *request;

    unsigned int gpio = 4; // GPIO 356 (PWM0-2), pin fisico 7 - donde esta el LED

    chip = gpiod_chip_open("/dev/gpiochip1");

    if(chip == NULL){
        perror("Error al abrir GPIO chip");
        return 1;
    }

    settings = gpiod_line_settings_new();

    if (settings == NULL)
    {
        perror("Error al crear settings");
        gpiod_chip_close(chip);
        return 1;
    }

    gpiod_line_settings_set_direction(settings,GPIOD_LINE_DIRECTION_OUTPUT);

    line_config = gpiod_line_config_new();

    if (line_config == NULL)
    {
        perror("Error al crear line config");
        gpiod_line_settings_free(settings);
        gpiod_chip_close(chip);
        return 1;
    }

    if (gpiod_line_config_add_line_settings(line_config,&gpio,1,settings) < 0)
    {
        perror("Error al agregar GPIO");
        gpiod_line_config_free(line_config);
        gpiod_line_settings_free(settings);
        gpiod_chip_close(chip);
        return 1;
    }

    request = gpiod_chip_request_lines(chip,NULL,line_config);

    if (request == NULL)
    {
        perror("Error al solicitar GPIO");
        gpiod_line_config_free(line_config);
        gpiod_line_settings_free(settings);
        gpiod_chip_close(chip);
        return 1;

    }
    
    //Enecender led
    gpiod_line_request_set_value(request,gpio,GPIOD_LINE_VALUE_ACTIVE);

    printf("LED encendido\n");

    sleep(1);
    //apagar led
    gpiod_line_request_set_value(request,gpio,GPIOD_LINE_VALUE_INACTIVE);

    printf("LED apagado\n");

    gpiod_line_request_release(request);
    gpiod_line_config_free(line_config);
    gpiod_line_settings_free(settings);
    gpiod_chip_close(chip);
    
    return 0;

}
