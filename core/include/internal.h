#pragma once

#include <stdint.h>



void internal_handle_svc(uint8_t svc_num, uint32_t svc_arg);

void internal_handle_systick(void);



