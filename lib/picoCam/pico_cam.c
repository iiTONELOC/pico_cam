#include "pico/stdlib.h"
#include <stdlib.h>
#include <stdio.h>
#include "../arducam/arducam.h"
#include "pico_cam.h"

// arducam config structure
struct arducam_config config;

/// @brief initializes the arducam camera
void initCamera()
{
    config.sccb = i2c0;
    config.sccb_mode = I2C_MODE_16_8;
    config.sensor_address = 0x24;
    config.pin_sioc = PIN_CAM_SIOC;
    config.pin_siod = PIN_CAM_SIOD;
    config.pin_resetb = PIN_CAM_RESETB;
    config.pin_xclk = PIN_CAM_XCLK;
    config.pin_vsync = PIN_CAM_VSYNC;
    config.pin_y2_pio_base = PIN_CAM_Y2_PIO_BASE;

    config.pio = pio0;
    config.pio_sm = 0;

    config.dma_channel = 0;
    config.image_buf = image_buf;
    config.image_buf_size = sizeof(image_buf);

    arducam_init(&config);
}

/// @brief takes a picture with the arducam and prints the
/// image data to the serial port
void takePicture()
{
    printf("Taking picture\r\n");
    arducam_capture_frame(&config);

    printf("img- ");
    for (int i = 0; i < 320 * 240; i++)
    {
        printf("%d ", config.image_buf[i]);
    }
    printf("\r\n");
}