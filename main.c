#include "pico/stdlib.h"
#include <stdlib.h>
#include <stdio.h>
#include "lib/echoLocation/echo_location.h"
#include "lib/picoCam/pico_cam.h"

// on-board LED pin (NON-WIFI PICO)
const uint LED_PIN = 25;

void main()
{
	// Initialize port for printf output
	stdio_init_all();

	// Initialize the on-board LED pin
	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN, GPIO_OUT);

	// Initialize echo location sensor
	init_echo_location();

	// Initialize Arducam
	// initCamera();

	// Loop forever
	while (true)
	{
		// check the distance of objects in front of the sensor
		echo_distance = check_distance();

		// If the distance is out of range, blink the LED
		// roughly 2inches to 12inches
		if (echo_distance < 6 || echo_distance > 30) // cm
		{
			// Blink LED
			gpio_put(LED_PIN, 1);
			sleep_ms(500);
			gpio_put(LED_PIN, 0);
			sleep_ms(500);
		}
		else
		{
			printf("Distance: %f cm\r\n", echo_distance);
		}
	}
}
