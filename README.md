# EDUCATIONAL-RED_PITAYA-125_14-2

Educational Project

A task scheduler implemented in C script for the PS (processor system) core 1 in Zynq7000 SoC, using API (Application Programming Interface) and BSP (Board Support Package) generated in Vivado with a basic VHDL HW: PS IP with some basic functionality enabled, a first
AXI connected GPIO IP with all on board led linked, a second AXI connected GPIO IP with a external Pin linked. 

- GPIO: Set one PS pin as output and one as a input;
- MAIN: when 3.3 V applied on input designed pin, output designed pin go HIGH and the eight onboard led turns on;
An interrupt on timer, drive a basic FIFO task scheduler: toggle the onboard led is the task 1 operation.
