#include "xadc.h"

XAdcPs XADC;
XAdcPs* XADC_Ptr = &XADC;

XAdcPs_Config* XADC_configPtr;

#define XPAR_AXI_XADC_0_DEVICE_ID 0

void XADC_init()
{
	XADC_configPtr = XAdcPs_LookupConfig(XPAR_AXI_XADC_0_DEVICE_ID); // This macro return a pointer of a internally created default struct to configure device.

	if(XADC_configPtr == NULL)
	{
		printf (" Config Lookup Failed !");

		return ;
	}
	else
	{
		printf (" Config Lookup OK !");
	}

	XAdcPs_CfgInitialize(XADC_Ptr, XADC_configPtr, XADC_configPtr->BaseAddress); // Initialize XADC... ATTENTION! make sure AXI address of XADC_IP in the PL is the same of XPAR_XDCFG_0_BASEADDR (and HIGH) and XPAR_PS7_DEV_CFG_0_BASEADDR (and HIGH) defined in xparameters.h file
																				// ...in this case BASE is 0x43C00000 and HIGH is 0x43C0FFFF, so I changed the preset value
	int Status = XAdcPs_SelfTest(XADC_Ptr);

	if(Status != XST_SUCCESS)
	{
		printf (" Self Test Failed !");
		return ;
	}
	else
	{
		printf (" Self Test OK !");
	}

	XAdcPs_SetSequencerMode(XADC_Ptr, XADCPS_SEQ_MODE_SINGCHAN);

	XAdcPs_SetSingleChParams(XADC_Ptr, XADCPS_CH_AUX_MIN, FALSE, FALSE, FALSE); // XADCPS_CH_AUX_MIN is AUX 0 channel correspond to G17 pin in this specific boar (red pitaya)
}

float XADC_coreTemp(void)
{
	u16 TempRawData = XAdcPs_GetAdcData(XADC_Ptr, XADCPS_CH_TEMP);

	float Temp = XAdcPs_RawToTemperature(TempRawData); // Recall library macro to convert raw data in C°

	return Temp;
}

float XADC_externalInput(void)
{
	u32 ExternalRawData = XAdcPs_GetAdcData(XADC_Ptr, XADCPS_CH_AUX_MIN); // read from external aux0 input pin

	float External = XAdcPs_RawToVoltage(ExternalRawData); // Recall library macro to convert raw data in volt (V)

	return External;
}


