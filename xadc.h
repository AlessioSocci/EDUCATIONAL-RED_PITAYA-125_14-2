/*
 * xadc.h
 *
 *  Created on: 03 gen 2020
 *      Author: Alessio
 */

#ifndef SRC_XADC_H_
#define SRC_XADC_H_

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xil_types.h"

#include "xgpio.h"
#include "xscutimer.h"
#include "xscugic.h"
#include "Xil_exception.h"
#include "xadcps.h"


void XADC_init(void);

float XADC_coreTemp(void);

float XADC_externalInput(void);

#endif /* SRC_XADC_H_ */
