/*
 * HW_interrupt.h
 *
 *  Created on: 15 apr 2020
 *      Author: Alessio
 */

#ifndef SRC_HW_INTERRUPT_H_
#define SRC_HW_INTERRUPT_H_

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xil_types.h"

#include "xgpio.h"
#include "xscutimer.h"
#include "xscugic.h"
#include "Xil_exception.h"
#include "xgpiops.h"



XGpioPs Button2; // MIO PS


void HW_interrupt_init();

#endif /* SRC_HW_INTERRUPT_H_ */
