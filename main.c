#include "pico/stdlib.h"
#include <stdlib.h>
#include <stdio.h>
#include "arducam/arducam.h"

uint8_t image_buf[320 * 240];

struct arducam_config config;

const uint led_pin = 25;
const uint btn_pin = 0;

int button_val = 0;
bool current_button_state = false;

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

void handleButtonPress()
{
	if (button_val == 0)
	{
		// button was presses change the state of the LED
		current_button_state = !current_button_state;
		// set the LED to the new state
		gpio_put(led_pin, current_button_state);

		takePicture();
	}
	else
	{
		// do nothing
	}
}

int main()
{
	// Initialize LED pin
	gpio_init(led_pin);
	gpio_set_dir(led_pin, GPIO_OUT);

	// Initialize button pin
	gpio_init(btn_pin);
	gpio_set_dir(btn_pin, GPIO_IN);

	// Initialize chosen serial port
	stdio_init_all();

	// Initialize Arducam
	initCamera();

	// Loop forever
	while (true)
	{
		// Read button
		button_val = gpio_get(btn_pin);

		printf("Button value: %d\r\n", button_val);

		// print the state of the button
		printf("Button state: %d\r\n", current_button_state);

		// CONTROL THE LED BASED ON THE BUTTON PRESS
		handleButtonPress();

		sleep_ms(250);
	}
}
