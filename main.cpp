#include <stdio.h>
#include "pico/stdlib.h"

#include "hardware/gpio.h"
#include "hardware/pio.h"

#include "main.h"
#include "pins.h"
#include "debug.h"
#include "data_line.pio.h"

PIO pio;
uint dl_yellow;
uint dl_red;

int main() {
    stdio_init_all();

    printf("Initializing pins...\n");
    init_pins();

    init_data_line_pio();

    // Enable this to enter debug loop (never exits)
    // debug_loop();

    while (true) {
        printf("LED Matrix Controller Running...\n");
        pio_sm_put_blocking(pio, dl_yellow, 0x21);
        pio_sm_put_blocking(pio, dl_yellow, 0x43);
        pio_sm_put_blocking(pio, dl_yellow, 0x65);
        pio_sm_put_blocking(pio, dl_yellow, 0x87);
        pio_sm_put_blocking(pio, dl_yellow, 0xa9);

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

void init_data_line_pio() {
    pio = pio0;
    uint offset = pio_add_program(pio, &data_line_program);
    dl_yellow = pio_claim_unused_sm(pio, true);
    data_line_program_init(pio, dl_yellow, offset, PIN_DATA_Y, PIN_CLOCK_Y, 1.0f);
    dl_red = pio_claim_unused_sm(pio, true);
    data_line_program_init(pio, dl_red, offset, PIN_DATA_R, PIN_CLOCK_R, 1.0f);
}
