######################################
# Top-Level makefile for iac-os
######################################


ALL_CSRC := $(APP_CSRC)

ALL_CINC := $(APP_CINC)

ALL_ASM	 := $(APP_ASM)




include $(OSPATH)/core/core.mk
include $(OSPATH)/hal/hal.mk

# this must be the last include
include $(OSPATH)/arch/$(DEVICE)/device.mk


