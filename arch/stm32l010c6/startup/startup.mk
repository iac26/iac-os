
S_ASM := $(OSPATH)/arch/$(DEVICE)/startup/crt0.S \
	 $(OSPATH)/arch/$(DEVICE)/startup/vectors.S 

S_SRC := $(OSPATH)/arch/$(DEVICE)/startup/crt1.c

S_INC := $(OSPATH)/ext/ARM/Core \
	 $(OSPATH)/ext/ST/STM32L0xx


LDSCRIPT := $(OSPATH)/arch/$(DEVICE)/startup/ld/$(DEVICE).ld



ALL_ASM += $(S_ASM)

ALL_CSRC += $(S_SRC)

ALL_CINC += $(S_INC)

include $(OSPATH)/arch/$(DEVICE)/startup/mk/$(DEVICE).mk
include $(OSPATH)/arch/$(DEVICE)/startup/mk/compiler.mk
include $(OSPATH)/arch/$(DEVICE)/startup/mk/rules.mk


