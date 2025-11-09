#include <stdio.h>
#include "pico/stdlib.h"

#include "hardware/gpio.h"

#include "debug.h"
#include "pins.h"

// Enters a debug loop allowing manual control of GPIO pins via STDIN.
void debug_loop() {
    while (true) {
        debug_step();
        sleep_ms(10);
    }
}

void debug_step() {
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
    if (c == EOF) return;
    if (c == '\r' || c == '\n') return;

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
}
