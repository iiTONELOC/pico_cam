cmake_minimum_required(VERSION 3.13)

# Pull in PICO SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Name our project
project(pico_cam C CXX ASM)

# set the correct standards for the pico
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(PICO_BOARD pico_w)

# init the Pi Pico SDK
pico_sdk_init()

add_executable(${PROJECT_NAME}
	lib/echoLocation/echo_location.c
	lib/picoCam/pico_cam.c
	lib/arducam/arducam.c
	lib/piFi/pi_fi.c
	lib/http/http.c

	main.c
)

# Generate the header file 
pico_generate_pio_header(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/image.pio)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR} )


# link the necessary libraries
target_link_libraries(${PROJECT_NAME}
	pico_stdlib
	pico_cyw43_arch_lwip_threadsafe_background
	pico_lwip_http
	hardware_dma
	hardware_i2c
	hardware_pio
	hardware_pwm
)

# Generate all output files for the project
pico_add_extra_outputs(${PROJECT_NAME})

# Enable usb/disable uart
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 1)
