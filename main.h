#ifndef MAIN_H
#define MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

// Initializes GPIO pins used by the LED matrix.
// This function performs hardware setup and does not return a value.
void init_pins(void);

// Enters a debug loop allowing manual control of GPIO pins via STDIN.
void debug_loop();

#ifdef __cplusplus
}
#endif

#endif // MAIN_H
