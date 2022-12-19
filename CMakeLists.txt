cmake_minimum_required(VERSION 3.13)

# Pull in PICO SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Name our project
project(pico_cam)

# init the Pi Pico SDK
pico_sdk_init()

add_executable(${PROJECT_NAME}
	lib/echoLocation/echo_location.c
	lib/picoCam/pico_cam.c
	lib/arducam/arducam.c
	main.c
)

# Generate the header file 
pico_generate_pio_header(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/image.pio)


# link the necessary libraries
target_link_libraries(${PROJECT_NAME}
	pico_stdlib
	hardware_dma
	hardware_i2c
	hardware_pio
	hardware_pwm
)

# Generate all output files for the project
pico_add_extra_outputs(${PROJECT_NAME})

# Enable usb/disable uart
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)
