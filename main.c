#include "pico/stdlib.h"
#include <stdlib.h>
#include <stdio.h>
#include "lib/echoLocation/echo_location.h"
#include "lib/picoCam/pico_cam.h"
#include "lib/piFi/pi_fi.h"

void main()
{
	// Initialize port for printf output
	stdio_init_all();

	// Initialize echo location sensor
	init_echo_location();

	// connect to network
	connect_to_network();
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
			// do nothing
		}
		else
		{
			printf("Distance: %f cm\r\n", echo_distance);
		}

		printf("NETWORK STATUS: %d\r\n", LINK_UP);

		sleep_ms(1000);
	}
}
