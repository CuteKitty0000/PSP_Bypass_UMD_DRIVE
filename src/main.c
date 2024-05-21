#include <pspsdk.h>
#include <pspkernel.h>
#include <systemctrl.h>
#include <kubridge.h>

#include "main.h"

PSP_MODULE_INFO("noumd", 0x1000, 1, 0);
PSP_MAIN_THREAD_ATTR(0);

int (*sceGpioPortRead)(void);

static u32 GpioPortRead[4];
static int discout;

static void ClearCaches(void) {
	sceKernelDcacheWritebackAll();
	kuKernelIcacheInvalidateAll();
}

static int sceGpioPortReadPatched(void) {
	int GPRValue = *((int *) 0xBE240004);
	
	if (discout != 0)
		GPRValue = GPRValue & 0xFBFFFFFF;

	return GPRValue;
}

static void PatchLowIO(void) {
	sceGpioPortRead = (void*)sctrlHENFindFunction("sceLowIO_Driver", "sceGpio_driver", 0x4250D44A);
	GpioPortRead[0] = (int)sceGpioPortRead;
	GpioPortRead[1] = (int)(sceGpioPortRead + 4);
	GpioPortRead[2] = (int)sceGpioPortRead;
	GpioPortRead[3] = (int)(sceGpioPortRead + 4);

	REDIRECT_FUNCTION(sceGpioPortRead, sceGpioPortReadPatched);
}

static void sctrlSESetDiscOut(int out) {
	u32 k1;
	
	k1 = pspSdkSetK1(0);

	PatchLowIO();
	ClearCaches();
	discout = out;
	sceKernelCallSubIntrHandler(4, 0x1A, 0, 0);
	sceKernelDelayThread(0x0000C350);

	pspSdkSetK1(k1);
}

static int main_thread(SceSize args, void *argp) {
	for (;;) {
		if (sceUmdCheckMedium() != 0) {
			sctrlSESetDiscOut(1);
		}

		sceKernelDelayThread(100000);
	}

	sceKernelExitDeleteThread(0);

	return 0;
}

int module_start(SceSize args, void *argp) {
	SceUID thid = sceKernelCreateThread("noumd_main", main_thread, 0x18, 0x1000, 0, NULL);
	if (thid >= 0)
		sceKernelStartThread(thid, args, argp);

	return 0;
}

int module_stop(SceSize args, void *argp) {
	return 0;
}