#include <stdio.h>
#include "pico/stdlib.h"

#include "hardware/gpio.h"

#include "pins.h"

void init_pins();

int main() {
    stdio_init_all();

    printf("Initializing pins...\n");
    init_pins();

    while (true) {
        printf(
            "strobe=%c output=%c clk_y=%c data_y=%c clk_r=%c data_r=%c\n",
            gpio_get_out_level(PIN_STROBE) ? '-' : '+',
            gpio_get_out_level(PIN_OUTPUT) ? '-' : '+',
            gpio_get_out_level(PIN_CLOCK_Y) ? '-' : '+',
            gpio_get_out_level(PIN_DATA_Y) ? '-' : '+',
            gpio_get_out_level(PIN_CLOCK_R) ? '-' : '+',
            gpio_get_out_level(PIN_DATA_R) ? '-' : '+'
        );
        fflush(stdout);

        int c = getchar(); // blocks until a char is available
        if (c == EOF) continue;
        if (c == '\r' || c == '\n') continue;

        bool level;
        switch (c) {
            // Output
            case 'e':
                level = gpio_get_out_level(PIN_OUTPUT);
                gpio_put(PIN_OUTPUT, !level);
                sleep_ms(100);
            case 'E':
                level = gpio_get_out_level(PIN_OUTPUT);
                gpio_put(PIN_OUTPUT, !level);
                break;

            // Strobe
            case 's':
                level = gpio_get_out_level(PIN_STROBE);
                gpio_put(PIN_STROBE, !level);
                sleep_ms(100);
            case 'S':
                level = gpio_get_out_level(PIN_STROBE);
                gpio_put(PIN_STROBE, !level);
                break;

            case 'y':
                level = gpio_get_out_level(PIN_DATA_Y);
                gpio_put(PIN_DATA_Y, !level);
                sleep_ms(100);
            case 'Y':
                level = gpio_get_out_level(PIN_DATA_Y);
                gpio_put(PIN_DATA_Y, !level);
                break;

            case 'h':
                level = gpio_get_out_level(PIN_CLOCK_Y);
                gpio_put(PIN_CLOCK_Y, !level);
                sleep_ms(100);
            case 'H':
                level = gpio_get_out_level(PIN_CLOCK_Y);
                gpio_put(PIN_CLOCK_Y, !level);
                break;

            case 'r':
                level = gpio_get_out_level(PIN_DATA_R);
                gpio_put(PIN_DATA_R, !level);
                sleep_ms(100);
            case 'R':
                level = gpio_get_out_level(PIN_DATA_R);
                gpio_put(PIN_DATA_R, !level);
                break;

            case 'f':
                level = gpio_get_out_level(PIN_CLOCK_R);
                gpio_put(PIN_CLOCK_R, !level);
                sleep_ms(100);
            case 'F':
                level = gpio_get_out_level(PIN_CLOCK_R);
                gpio_put(PIN_CLOCK_R, !level);
                break;

            // default:
            //     printf("Unknown command: '%c' (0x%02x)\n", (char)c, c);
            //     break;
        }

        sleep_ms(10);
    }
}

void init_pins() {
    // All pins are output, pulled high and set to 0 for a truthy state
    gpio_init(PIN_STROBE);
    gpio_set_dir(PIN_STROBE, true);
    gpio_pull_down(PIN_STROBE);
    gpio_put(PIN_STROBE, false); // Start low (enabled)

    gpio_init(PIN_OUTPUT);
    gpio_set_dir(PIN_OUTPUT, true);
    gpio_pull_down(PIN_OUTPUT);
    gpio_put(PIN_OUTPUT, false); // Start low (enabled)

    gpio_init(PIN_CLOCK_Y);
    gpio_set_dir(PIN_CLOCK_Y, true);
    gpio_pull_down(PIN_CLOCK_Y);
    gpio_put(PIN_CLOCK_Y, true);

    gpio_init(PIN_DATA_Y);
    gpio_set_dir(PIN_DATA_Y, true);
    gpio_pull_down(PIN_DATA_Y);
    gpio_put(PIN_DATA_Y, true);

    gpio_init(PIN_CLOCK_R);
    gpio_set_dir(PIN_CLOCK_R, true);
    gpio_pull_down(PIN_CLOCK_R);
    gpio_put(PIN_CLOCK_R, true);

    gpio_init(PIN_DATA_R);
    gpio_set_dir(PIN_DATA_R, true);
    gpio_pull_down(PIN_DATA_R);
    gpio_put(PIN_DATA_R, true);
}