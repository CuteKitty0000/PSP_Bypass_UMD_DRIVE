TARGET 			= Bypass UMD
OBJS 			= main.o imports.o exports.o

CFLAGS 			= -O2 -Os -G0 -Wall
CXXFLAGS 		= $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS 		= $(CFLAGS)

BUILD_PRX 		= 1
PRX_EXPORTS 		= exports.exp

USE_PSPSDK_LIBS 	= 1
USE_PSPSDK_LIBC 	= 1

LIBS 			= -lpspsystemctrl_user -lpspkubridge

PSPSDK 			= $(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build_prx.mak