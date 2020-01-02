
#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"

#include "xgpio.h"
#include "xscutimer.h"
#include "xscugic.h"
#include "Xil_exception.h"

extern uint8_t arrival_task0_flag;
extern uint8_t arrival_task1_flag;

void XScuTimer_init(void);

