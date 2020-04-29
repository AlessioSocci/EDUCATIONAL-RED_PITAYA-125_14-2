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

// Board Support (BSP) file
#include <stdio.h>
#include "platform.h"
#include "xmbox.h"
#include "xmutex.h"

int main()
{
	init_platform();

	// MAIL BOX
	XMbox MBox;
	XMbox_Config* MBoxConfigPtr;

	MBoxConfigPtr = XMbox_LookupConfig(XPAR_MBOX_1_DEVICE_ID); // make sure that the address in xparameters.h (...of Microblaze BSP) is the same of the MBox PL-IP address, here is
    															// BASE is 0x43810000U and HIGH is 0x4381FFFFU
	int j = XMbox_CfgInitialize(&MBox, MBoxConfigPtr,  MBoxConfigPtr->BaseAddress);

	u32 MBoxTX_data = 19; // Buffer of TX data to mailbox

    // MUTEX
	XMutex Mutex;
	XMutex_Config* MutexConfigPtr;

	MutexConfigPtr = XMutex_LookupConfig(XPAR_MUTEX_0_IF_1_DEVICE_ID);
	XMutex_CfgInitialize(&Mutex, MutexConfigPtr, MutexConfigPtr->BaseAddress);


	XMbox_WriteBlocking(&MBox, &MBoxTX_data, 4); // send message to mailbox, where the hard core processor A9 can read it

	for(int j=0; j < 3000; j++); // wait...


	int i = 0;

    while(1)
    {
    	if(i == 10)
    	{
    		XMutex_Lock(&Mutex, 1); // lock mutex
    	}

    	i++;
    }

//    cleanup_platform();

    return 0;
}
