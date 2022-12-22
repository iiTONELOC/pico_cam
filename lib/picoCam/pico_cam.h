#ifndef PICO_CAM_H
#define PICO_CAM_H
#include "pico/stdlib.h"
#include "../arducam/arducam.h"
#include <stdlib.h>
#include <stdio.h>

void pico_cam_init();
struct arducam_config *pico_cam_capture();

#endif
