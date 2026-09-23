// 3GPIOIN: botón (pull-up, activo en bajo) -> LED, con libgpiod v2
// Compilar: gcc main.c -o build/3GPIOIN -lgpiod
#include <errno.h>
#include <gpiod.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define CHIP_PATH     "/dev/gpiochip1"
#define LED_OFFSET    4
#define BUTTON_OFFSET 6
#define CONSUMER      "3GPIOIN"

static volatile sig_atomic_t running = 1;

static void on_signal(int sig)
{
    (void)sig;
    running = 0;
}

int main(void)
{
    struct gpiod_chip *chip = NULL;
    struct gpiod_line_settings *led_settings = NULL;
    struct gpiod_line_settings *button_settings = NULL;
    struct gpiod_line_config *line_config = NULL;
    struct gpiod_request_config *req_config = NULL;
    struct gpiod_line_request *request = NULL;
    unsigned int led = LED_OFFSET;
    unsigned int button = BUTTON_OFFSET;
    int ret = 1;

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = on_signal;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    chip = gpiod_chip_open(CHIP_PATH);
    if (!chip) {
        fprintf(stderr, "Error al abrir %s: %s\n", CHIP_PATH, strerror(errno));
        return 1;
    }

    // LED: salida, apagado al inicio
    led_settings = gpiod_line_settings_new();
    if (!led_settings) {
        fprintf(stderr, "Error al crear LED settings: %s\n", strerror(errno));
        goto cleanup;
    }
    gpiod_line_settings_set_direction(led_settings, GPIOD_LINE_DIRECTION_OUTPUT);
    gpiod_line_settings_set_output_value(led_settings, GPIOD_LINE_VALUE_INACTIVE);

    // Botón: entrada con pull-up; active_low => presionado = ACTIVE
    button_settings = gpiod_line_settings_new();
    if (!button_settings) {
        fprintf(stderr, "Error al crear BUTTON settings: %s\n", strerror(errno));
        goto cleanup;
    }
    gpiod_line_settings_set_direction(button_settings, GPIOD_LINE_DIRECTION_INPUT);
    gpiod_line_settings_set_bias(button_settings, GPIOD_LINE_BIAS_PULL_UP);
    gpiod_line_settings_set_active_low(button_settings, true);

    line_config = gpiod_line_config_new();
    if (!line_config) {
        fprintf(stderr, "Error al crear line config: %s\n", strerror(errno));
        goto cleanup;
    }
    if (gpiod_line_config_add_line_settings(line_config, &led, 1, led_settings) < 0 ||
        gpiod_line_config_add_line_settings(line_config, &button, 1, button_settings) < 0) {
        fprintf(stderr, "Error al agregar líneas: %s\n", strerror(errno));
        goto cleanup;
    }

    req_config = gpiod_request_config_new();
    if (!req_config) {
        fprintf(stderr, "Error al crear request config: %s\n", strerror(errno));
        goto cleanup;
    }
    gpiod_request_config_set_consumer(req_config, CONSUMER);

    request = gpiod_chip_request_lines(chip, req_config, line_config);
    if (!request) {
        fprintf(stderr, "Error al solicitar GPIO: %s (errno=%d)\n", strerror(errno), errno);
        goto cleanup;
    }

    while (running) {
        enum gpiod_line_value value = gpiod_line_request_get_value(request, button);
        if (value == GPIOD_LINE_VALUE_ERROR) {
            fprintf(stderr, "Error al leer botón: %s\n", strerror(errno));
            break;
        }
        gpiod_line_request_set_value(request, led,
            value == GPIOD_LINE_VALUE_ACTIVE ? GPIOD_LINE_VALUE_ACTIVE
                                             : GPIOD_LINE_VALUE_INACTIVE);
        usleep(10000);
    }

    ret = 0;

cleanup:
    if (request)
        gpiod_line_request_release(request);
    gpiod_request_config_free(req_config);
    gpiod_line_config_free(line_config);
    gpiod_line_settings_free(button_settings);
    gpiod_line_settings_free(led_settings);
    gpiod_chip_close(chip);
    return ret;
}

