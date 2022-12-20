#include <stdio.h>
#include "pi_fi.h"
#include ".pi_fi_env.h"
#include "pico/stdlib.h"
#include "hardware/vreg.h"
#include "hardware/clocks.h"
#include "pico/cyw43_arch.h"

uint8_t LINK_UP = 0;

/// @brief Initializes the Wi-Fi hardware
/// @return -1 if the hardware could not be initialized, 0 if the hardware was initialized
int init_pi_fi(void)
{
    printf("Initializing Wi-Fi hardware\r\n");
    // initialize the wifi hardware
    cyw43_arch_init_with_country(CYW43_COUNTRY_USA);

    // check if the hardware was initialized
    if (!cyw43_is_initialized(&cyw43_state))
    {
        printf("Error: hardware not initialized\r\n");
        return -1;
    }
    else
    {
        printf("Hardware initialized\r\n");
    }

    return 0;
}

/// @brief Connects to the network using the credentials defined in .pi_fi_env.h
/// @return -1 if the hardware could not be initialized, 0 if the hardware was initialized
int connect_to_network()
{
    printf("Connecting to network\r\n");

    // initialize the wifi hardware

    int init_result = init_pi_fi();

    if (init_result != 0)
    {
        return -1;
    }
    else
    {
        // enable station mode
        cyw43_arch_enable_sta_mode();

        // connect to the network

        int connect_result = cyw43_arch_wifi_connect_timeout_ms(
            WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 10000);

        if (connect_result == 0)
        {
            printf("Connected to network\r\n");
            LINK_UP = 1;
            return 0;
        }
        else
        {
            printf("Error: could not connect to network\r\n");
            LINK_UP = 0;
            return -1;
            printf("Error: %d", connect_result);
        }
    }
}
