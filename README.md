# EDUCATIONAL-RED_PITAYA-125_14-2

Educational Project

A task scheduler implemented in C script for the PS (processor system) core 1 in Zynq7000 SoC, using API (Application Programming Interface) and BSP (Board Support Package) generated in Vivado with a basic VHDL HW: PS IP with some basic functionality enabled, a first
AXI connected GPIO IP with all on board led linked, a second AXI connected GPIO IP with a external Pin linked. 

- GPIO: Set one PS pin as output and one as a input;

- XADC: Read internal core tmperature, sensor is yet in zynq package and for this purpose, ther is no need to instanciate block XADC IP.
(XADC is necessary for external voltage conversion);
Read external non differential analog input by instanciate IP block XADC in Vivado; external input is provided by a 200 kOhm linear potentiometer between 3.3 V and 0 V . On board resistive divider scale this value between 1.8 V and 0 V accpeeted by Zynq ADC.
Reading are effectuated in polling mode (interrupt or DMA not yet being configured).
  
- MAIN: when 3.3 V applied on input designed pin, output designed pin go HIGH and the eight onboard led turns on;
An interrupt on timer, drive a basic FIFO task scheduler: toggle the onboard led is the task 1 operation, read internal core temperature and external analog input in task 2.
