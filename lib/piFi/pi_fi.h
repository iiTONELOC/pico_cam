
#ifndef _PIFI_H_
#define _PIFI_H_

#include <stdio.h>
#include ".pi_fi_env.h"
#include "pico/stdlib.h"
#include "hardware/vreg.h"
#include "hardware/clocks.h"
#include "pico/cyw43_arch.h"

extern uint8_t LINK_UP;
int init_pi_fi(void);
int connect_to_network();
#endif
