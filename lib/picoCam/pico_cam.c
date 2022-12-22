#include "pico/stdlib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../arducam/arducam.h"
#include "pico_cam.h"

// arducam config structure

uint8_t image_buf[320 * 240];

struct arducam_config pico_cam_config;

/// @brief initializes the arducam camera
void pico_cam_init()
{
    pico_cam_config.sccb = i2c0;
    pico_cam_config.sccb_mode = I2C_MODE_16_8;
    pico_cam_config.sensor_address = 0x24;
    pico_cam_config.pin_sioc = PIN_CAM_SIOC;
    pico_cam_config.pin_siod = PIN_CAM_SIOD;
    pico_cam_config.pin_resetb = PIN_CAM_RESETB;
    pico_cam_config.pin_xclk = PIN_CAM_XCLK;
    pico_cam_config.pin_vsync = PIN_CAM_VSYNC;
    pico_cam_config.pin_y2_pio_base = PIN_CAM_Y2_PIO_BASE;

    pico_cam_config.pio = pio0;
    pico_cam_config.pio_sm = 0;

    pico_cam_config.dma_channel = 0;
    pico_cam_config.image_buf = image_buf;
    pico_cam_config.image_buf_size = sizeof(image_buf);

    arducam_init(&pico_cam_config);
}

/// @brief takes a picture with the arducam and prints the
/// image data to the serial port
struct arducam_config *pico_cam_capture()
{
    printf("Taking picture\r\n");
    arducam_capture_frame(&pico_cam_config);

    return &pico_cam_config;
}