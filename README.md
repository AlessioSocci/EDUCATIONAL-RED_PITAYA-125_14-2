# EDUCATIONAL-RED_PITAYA-125_14-2

Educational Project

A task scheduler implemented in C script for the PS (processor system) core 1 in Zynq7000 SoC, using API (Application Programming Interface) and BSP (Board Support Package) generated in Vivado with a basic VHDL HW: PS IP with some basic functionality enabled, a first
AXI connected GPIO IP with all the on board led linked, a second AXI connected GPIO IP with external Pin linked and an XADC IP block with external pin connected to AUX 0 input.

- GPIO: Set one AXI GPIO PL IP pin as output and another one AXI GPIO PL IP pin as input; GPIO IP are connected via AXI bus to processor.

- PS MIO: Set pin 13 of PS MIO as output. PS MIO are pin directly connected to the processor, bypassing the FPGA logic.  

- XADC: Read internal core tmperature, sensor is yet in zynq package and for this purpose, ther is no need to instanciate block XADC IP.
(XADC is necessary for external voltage conversion);
Read external non differential analog input by instanciate IP block XADC in Vivado; external input is provided by a 200 kOhm linear potentiometer between 3.3 V and 0 V . On board resistive divider scale this value between 1.8 V and 0 V accpeeted by Zynq ADC.
Reading are effectuated in polling mode (interrupt or DMA not yet being configured).
  
- MAIN: when 3.3 V applied on input designed pin, output designed pin go HIGH and the eight onboard led turns on;
An interrupt on timer, drive a basic FIFO task scheduler: toggle the onboard led, connected to AXI GPIO, and PS MIO output pin 13 in task 1, read internal core temperature in task 2, read external AXI GPIO analog input in polling, out of task domain and into infinite loop of main function.
