#include "xadc.h"

XAdcPs XADC;
XAdcPs* XADC_Ptr = &XADC;

XAdcPs_Config* XADC_configPtr;

#define XPAR_AXI_XADC_0_DEVICE_ID 0

void XADC_init()
{
	XADC_configPtr = XAdcPs_LookupConfig(XPAR_AXI_XADC_0_DEVICE_ID); // This macro return a pointer of a internally created default struct to configure device.

	XAdcPs_CfgInitialize(XADC_Ptr, XADC_configPtr, XADC_configPtr->BaseAddress); // Initialize XADC
}

float XADC_getCoreTemp(void)
{
	u16 TempRawData = XAdcPs_GetAdcData(XADC_Ptr, XADCPS_CH_TEMP);

	float Temp = XAdcPs_RawToTemperature(TempRawData); // Recall library macro to convert raw data in C°

	return Temp;
}



