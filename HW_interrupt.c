/*
 * HW_interrupt.c
 *
 *  Created on: 15 apr 2020
 *      Author: Alessio
 */


#include "HW_interrupt.h"
#include "time.h"

#define HW_INTERRUPT_PIN 12

XGpioPs PS_input;
XGpioPs* PS_input_ptr = &PS_input;

XScuGic gic2;
XScuGic* gic_Ptr2 = &gic2;

XScuGic_Config *gic2_configPtr;

void XGpio_IntrHandler(void *CallBackRef, int Bank, u32 Status)
{
	PS_input_ptr = (XGpioPs *)CallBackRef;

	XGpioPs_IntrClearPin(PS_input_ptr, HW_INTERRUPT_PIN);
}

void HW_interrupt_init()
{
	XGpioPs_Config *GPIOPsConfigPtr = XGpioPs_LookupConfig(XPAR_PS7_GPIO_0_DEVICE_ID);

	XGpioPs_CfgInitialize(PS_input_ptr, GPIOPsConfigPtr, GPIOPsConfigPtr->BaseAddr);

	XGpioPs_SetDirectionPin(PS_input_ptr, HW_INTERRUPT_PIN, 1);

	Xil_ExceptionInit();

	gic2_configPtr = XScuGic_LookupConfig(XPAR_SCUGIC_SINGLE_DEVICE_ID); // initialize the GIC

	XScuGic_CfgInitialize(gic_Ptr2, gic2_configPtr, gic2_configPtr->CpuBaseAddress);

	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XScuGic_InterruptHandler, gic_Ptr2); // connect to the hardware

	XScuGic_Connect(gic_Ptr2, XPS_GPIO_INT_ID, (Xil_ExceptionHandler)XGpioPs_IntrHandler, (void *)PS_input_ptr); // set up the GPIO interrupt

	XGpioPs_SetIntrTypePin(PS_input_ptr, HW_INTERRUPT_PIN, XGPIOPS_IRQ_TYPE_EDGE_RISING);

	XGpioPs_SetCallbackHandler(PS_input_ptr, (void *)PS_input_ptr, (void *)XGpio_IntrHandler); // Set the handler for gpio interrupts.

	XGpioPs_IntrEnablePin(PS_input_ptr, HW_INTERRUPT_PIN); // Enable the GPIO interrupts of Bank 0.

	XScuGic_Enable(gic_Ptr2, XPS_GPIO_INT_ID); // Enable the interrupt for the GPIO device.

	Xil_ExceptionEnableMask(XIL_EXCEPTION_IRQ); // Enable interrupts in the Processor.
}



