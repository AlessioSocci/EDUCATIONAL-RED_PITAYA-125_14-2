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
#include "xil_printf.h"
#include "xil_types.h"

#include "xgpio.h"
#include "xscutimer.h"
#include "xscugic.h"
#include "Xil_exception.h"
#include "xadcps.h"
#include "xgpiops.h"

#include "time.h"
#include "xadc.h"
#include "HW_interrupt.h"

int main()
{
	XGpio Led, Button; // GPIO PL

	XGpio_Initialize(&Led, XPAR_AXI_GPIO_0_DEVICE_ID);
	XGpio_Initialize(&Button, XPAR_AXI_GPIO_1_DEVICE_ID); // Initialize XADC... ATTENTION! make sure AXI address of GPIO_IP in the PL is the same of XPAR_AXI_GPIO_1_BASEADDR (and HIGH) defined in xparameters.h file
	// ...in this case BASE is 0x41210000 and HIGH is 0x4121FFFF, here I change the address of GPIO_IP in Vivado and leave as it the default defined address in SDK

	XGpio_SetDataDirection(&Led, 1, 0x00);
	XGpio_SetDataDirection(&Button, 1, 0xFF);


	XGpioPs PS_output; // MIO PS

	XGpioPs_Config *GPIOPsConfigPtr = XGpioPs_LookupConfig(XPAR_PS7_GPIO_0_DEVICE_ID);

	XGpioPs_CfgInitialize(&PS_output, GPIOPsConfigPtr, GPIOPsConfigPtr->BaseAddr);

	XGpioPs_SetDirectionPin(&PS_output, 13, 1); // PS pin 13 set as output

	XGpioPs_SetOutputEnablePin(&PS_output, 13, 1); // enable output for pin 13 of PS

	XADC_init();

	XScuTimer_init();

	int i = 0;

	while(1)
	{
		if(XGpio_DiscreteRead(&Button, 1)) // control button state is place out of any task, in main loop
		{
			XGpio_DiscreteWrite(&Led, 1, 0x000000FF); // When button is pressed, turn on the eight led
		}

		if (arrival_task0_flag == 1) // task 0 control flag
		{
			arrival_task0_flag = 0; // reset flag of task

			if((i % 2) == 0) // turn on the first four led when variable "i" is even, else turn the second four.
			{
				XGpio_DiscreteWrite(&Led, 1, 0x0000000F);

				XGpioPs_WritePin(&PS_output, 13, 1); // PS pin 13 set high
			}
			else
			{
				XGpio_DiscreteWrite(&Led, 1, 0x000000F0);

				XGpioPs_WritePin(&PS_output, 13, 0); // PS pin 13 set low
			}

			i++;
		}


		if (arrival_task1_flag == 1) // task 1  control flag
		{
			arrival_task1_flag = 0; // reset flag of task

			float coreTemp = XADC_coreTemp(); // read analog value of internal core temperature sensor

			float adc_data = XADC_externalInput(); // read analog value of external input (Auxiliary input 0 in this case)
		}

	}


//    cleanup_platform();

    return 0;
}
