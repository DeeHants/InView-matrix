#include <stdio.h>
#include "pico/stdlib.h"

#include "hardware/gpio.h"

#include "main.h"
#include "pins.h"
#include "debug.h"

int main() {
    stdio_init_all();

    printf("Initializing pins...\n");
    init_pins();

    // Enable this to enter debug loop (never exits)
    // debug_loop();

    while (true) {
        printf("LED Matrix Controller Running...\n");
        debug_step();
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
