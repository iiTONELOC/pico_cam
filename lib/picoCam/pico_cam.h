#ifndef PICO_CAM_H
#define PICO_CAM_H
#include "pico/stdlib.h"
#include "../arducam/arducam.h"
#include <stdlib.h>
#include <stdio.h>

extern uint8_t image_buf[320 * 240];

void picoCam_init();
void picoCam_capture();

#endif
