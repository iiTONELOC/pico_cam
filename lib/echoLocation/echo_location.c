#include "pico/stdlib.h"
#include "echo_location.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

// Echo location sensor pins
uint ECHO_PIN = 26;
uint TRIG_PIN = 27;

// echo location sensor variables
float echo_distance = 0;

/// @brief Measures the length (in microseconds) of a pulse on the pin.
/// @param pin  pin number
/// @param state state to measure (0 or 1)
/// @return length of the pulse in microseconds
unsigned long pulseIn(uint pin, uint state)
{
    unsigned long width = 0; // keep initialization out of time critical area

    // wait for any previous pulse to end
    while (gpio_get(pin) == state)
        ;
    // wait for the pulse to start
    while (gpio_get(pin) != state)
        ;
    // wait for the pulse to stop
    while (gpio_get(pin) == state)
    {
        width++;
    }

    // divide by 10 to convert to microseconds
    return width / 10;
}

/// @brief Checks the distance of objects in front of the sensor
/// @return the distance in centimeters
float check_distance()
{
    // wite out to trig pin for 2 microseconds at a low level to clear the sensor
    gpio_put(TRIG_PIN, 0);
    sleep_us(2);

    // write out to trig pin for 10 microseconds at a high level to trigger the sensor
    gpio_put(TRIG_PIN, 1);
    sleep_us(10);
    // set the trig pin back to low
    gpio_put(TRIG_PIN, 0);

    // read the echo pin to get the pulse width
    // we take the pulse width and divide it by 2 because
    // the pulse goes out and back
    float pulse_width = pulseIn(ECHO_PIN, 1) / 2;

    // calculate how far away the object is based on the pulse width
    // speed of sound = 340 m/s

    // 340 m/s = 29.1 us/cm
    float _distance_cm = pulse_width / 29.1;

    return _distance_cm;
}

/// @brief initializes the echo location sensor
void init_echo_location()
{
    // Initialize echo location sensor pins

    // echo is our input pin
    gpio_init(ECHO_PIN);
    gpio_set_dir(ECHO_PIN, GPIO_IN);

    // trig is our output pin and we start it low
    gpio_init(TRIG_PIN);
    gpio_set_dir(TRIG_PIN, GPIO_OUT);
    gpio_put(TRIG_PIN, 0);
}
