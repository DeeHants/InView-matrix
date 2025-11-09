#ifndef DEBUG_H
#define DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

// Enters a debug loop allowing manual control of GPIO pins via STDIN.
void debug_loop();
void debug_step();

#ifdef __cplusplus
}
#endif

#endif // DEBUG_H
