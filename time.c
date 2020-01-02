
#include "time.h"


XScuTimer Timer;
XScuGic Intc;

uint32_t arrival_task0_counter = 0;

uint32_t arrival_task0_time = 50;

uint8_t arrival_task0_flag = 0;


uint32_t arrival_task1_counter = 0;

uint32_t arrival_task1_time = 10;

uint8_t arrival_task1_flag = 0;


void TimerIntrHandler(void *CallBackRef)
{
    XScuTimer *TimerInstancePtr = (XScuTimer *) CallBackRef;

    XScuTimer_ClearInterruptStatus(TimerInstancePtr);

    printf("Timer Interrupt occur now! \n\r");

    task_scheduler(); // call scheduler
}


void SetupInterruptSystem(XScuGic *GicInstancePtr, XScuTimer *TimerInstancePtr, u16 TimerIntrId)
{
	XScuGic_Config *IntcConfig; // GIC config

	Xil_ExceptionInit();

	IntcConfig = XScuGic_LookupConfig(XPAR_SCUGIC_SINGLE_DEVICE_ID); // initialize the GIC

	XScuGic_CfgInitialize(GicInstancePtr, IntcConfig, IntcConfig->CpuBaseAddress);

	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XScuGic_InterruptHandler, GicInstancePtr); //connect to the hardware

	XScuGic_Connect(GicInstancePtr, TimerIntrId, (Xil_ExceptionHandler)TimerIntrHandler, (void *)TimerInstancePtr); // set up the timer interrupt


	XScuGic_Enable(GicInstancePtr, TimerIntrId); //enable the interrupt for the Timer at GIC (Global Interrupt Controller)

	XScuTimer_EnableInterrupt(TimerInstancePtr); // enable interrupt on the timer

	Xil_ExceptionEnableMask(XIL_EXCEPTION_IRQ); // enable interrupts in the Processor
}


void XScuTimer_init()
{
	XScuTimer_Config* ConfigPtr;

	ConfigPtr = XScuTimer_LookupConfig(XPAR_PS7_SCUTIMER_0_DEVICE_ID); // XScuTimer config by a struc pointer returned type

	XScuTimer_CfgInitialize(&Timer, ConfigPtr, ConfigPtr->BaseAddr); // XScuTimer init

	XScuTimer_EnableAutoReload(&Timer);

	SetupInterruptSystem(&Intc, &Timer, XPAR_SCUTIMER_INTR); // call function to set interrupt on timer

	XScuTimer_LoadTimer(&Timer, 0x00FFFFFF); // load a value as a threshold to timer

	XScuTimer_Start(&Timer); // start timer
}


void task_scheduler(void)
{
	arrival_task0_counter++;
	arrival_task1_counter++;

	if(arrival_task0_counter == arrival_task0_time)
	{
		arrival_task0_counter = 0;
		arrival_task0_flag = 1;
	}

	if(arrival_task1_counter == arrival_task1_time)
	{
		arrival_task1_counter = 0;
		arrival_task1_flag = 1;
	}

}
