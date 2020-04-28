# EDUCATIONAL-RED_PITAYA-125_14-2

Educational Project

A FCFS (first come first served) task scheduler drived by a system timer and interrupt, are implemented in C script for the PS (processor system) core 1 in Zynq7000 SoC, using API (Application Programming Interface) and BSP (Board Support Package) generated in Vivado with a basic VHDL HW: PS IP with some basic functionality enabled, a first
AXI connected GPIO IP with eight of the ten on board led linked, a second AXI connected GPIO IP with external Pin linked and an XADC IP block with external pin connected to AUX 0 input. 
A MicroBlaze soft core processor and a mail-box are created in PL and connected by AXI bus. 

ARM CORTEX A9 Core 1 processor:

- GPIO: Set one AXI GPIO PL IP pin as output and, in another one AXI GPIO PL IP, one pin as input; GPIO IP are connected via AXI bus to processor.

- PS MIO: Set pin 0 and 7 of PS MIO as output, it's connected at two on-board led and at the other side are directly connected to the processor, bypassing the FPGA logic.
Set pin 13 as input, with a pull-down resistor 10 kOhm externally cabled. 

- XADC: Read internal core tmperature, sensor is yet in zynq package and for this purpose, ther is no need to instanciate block XADC IP.
(XADC is necessary for external voltage conversion);
Read external non differential analog input by instanciate IP block XADC in Vivado; external input is provided by a 200 kOhm linear potentiometer between 3.3 V and 0 V . On board resistive divider scale this value between 1.8 V and 0 V accpeeted by Zynq ADC.
Reading are effectuated in polling mode (interrupt or DMA not yet being configured).
 
- HW-INTERRUPT: the primary example of an hardware interrupt is a GPIO interrupt. Here a PS MIO 12, gpio directly connected to processor, is used for trigger the correlated interrut routine, where, at its inside, only a clearing of his interrupt flag is executed. Interrupt is predisposed to take place on the rising edge of voltage applied at pin. (as a temporally solution to allow normal execution of other interrupt used in this educational example, the API function to configure ps gpio interrupt has been modified: " XScuGic_Stop(InstancePtr); " recalled in " s32  XScuGic_CfgInitialize(XScuGic *InstancePtr, XScuGic_Config *ConfigPtr, u32 EffectiveAddr) " ) 
has been commented. ).

- MAIN: when 3.3 V are applied on input designed pin, output designed pin go HIGH and the eight onboard led turns on;
An interrupt on timer, drive a basic FCFS task scheduler: toggle the eight onboard led, connected to AXI GPIO, and the first led connected directly to processor in task 0, read internal core temperature in task 1, read external AXI GPIO analog input and PS MIO input in polling, out of task domain and into infinite loop of main function. If button of AXI GPIO is pressed, the eight led are on, else blink with tasko; if button are pressed, the two led connected to processor are on, else the second is off and the first blink with task0. In task2, read the 4 Byte message in mail mbox, it's the message from Microblaze.  

MICROBLAZE soft-processor :

- MAIN: initialize mail box with its BSP API and send to it a 4 Byte message in infinite while loop. 





