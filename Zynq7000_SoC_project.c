/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * Zynq7000_SoC_project.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xil_types.h"

#include "xgpio.h"
#include "xscutimer.h"
#include "xscugic.h"
#include "Xil_exception.h"
#include "xadcps.h"

#include "time.h"
#include "xadc.h"


int main()
{
	init_platform();

	XGpio Led = {0x41200000, 0x11111111, 0, 0};
	XGpio Button = {0x41210000, 0x00000000, 0, 0};

	XGpio_Initialize(&Led, XPAR_AXI_GPIO_0_DEVICE_ID);
	XGpio_Initialize(&Button, XPAR_AXI_GPIO_1_DEVICE_ID);

	XGpio_SetDataDirection(&Button, 1, 0xFFFFFFFF);


	XScuTimer_init();

	XADC_init();


	int i = 0;


	while(1)
	{

		if(XGpio_DiscreteRead(&Button, 1)) // control button state is place out of any task, in main loop
		{
			XGpio_DiscreteWrite(&Led, 1, 0xFFFFFFFF); // When button is pressed, turn on the eight led
		}


		if (arrival_task0_flag == 1) // task 0 control flag
		{
			arrival_task0_flag = 0; // reset flag of task

			if((i % 2) == 0) // turn on led when variable i is even, else turn off
			{
				XGpio_DiscreteWrite(&Led, 1, 0xFFFFFFFF);
			}
			else
			{
				XGpio_DiscreteWrite(&Led, 1, 0x00000000);
			}
			i++;
		}

		if (arrival_task1_flag == 1) // task 1  control flag
		{
			arrival_task1_flag = 0; // reset flag of task

			float coreTemp = XADC_getCoreTemp(); // read analog value of internal core temperature sensor
		}

	}


    cleanup_platform();

    return 0;
}
