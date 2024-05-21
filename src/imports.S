	.set noreorder

#include "pspstub.s"

	STUB_START	"InterruptManagerForKernel",0x00010000,0x00010005
	STUB_FUNC	0x8BE96A2E,sceKernelCallSubIntrHandler
	STUB_END

	STUB_START	"sceUmd",0x00010011,0x00010005
	STUB_FUNC	0x46EBB729,sceUmdCheckMedium
	STUB_END