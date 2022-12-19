# Pico Cam &#128247;

is a development repo for projects using a Raspberry Pi Pico and an ArduCam HM0360 camera.

## Code disclaimer

The arudcam folder primarily comes from the [https://github.com/ArduCAM/RPI-Pico-Cam/tree/master/rp2040_hm01b0](https://github.com/ArduCAM/RPI-Pico-Cam/tree/master/rp2040_hm01b0) repo. The website for the repo provided with my purchase of the camera has been moved or no longer exists. I was able to find almost the correct code to run the camera but had to modify the init sequence to load the correct data into the registers. I was able to find the correct data for the HM0360 in ArduCam's examples for the Pico4ML AdapterBoard. The code can be found here : [https://github.com/ArduCAM/Pico4ML_AdapterBoard/blob/main/HM0360/lib/arducam/hm0360_init.h](https://github.com/ArduCAM/Pico4ML_AdapterBoard/blob/main/HM0360/lib/arducam/hm0360_init.h).

## Motion Activation and Obstacle Avoidance

This code uses #8 and #9 from the Keyestudio Pi Pico Sensor Kit. The documentation for these parts can be found here: [Keyestudio Wiki](<https://wiki.keyestudio.com/KS3023(3023F)_Keyestudio_Raspberry_Pi_Pico_37_in_1_Sensor_Kit>).
