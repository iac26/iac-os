###########################################
# Global makefile rules
###########################################


# Output directory and files
ifeq ($(BUILDDIR),)
  BUILDDIR = out
endif
ifeq ($(BUILDDIR),.)
  BUILDDIR = out
endif

OUTFILES := $(BUILDDIR)/$(PROJECT).elf \
            $(BUILDDIR)/$(PROJECT).hex \
            $(BUILDDIR)/$(PROJECT).bin \
            $(BUILDDIR)/$(PROJECT).dmp \
            $(BUILDDIR)/$(PROJECT).list

OBJDIR    := $(BUILDDIR)/obj
LSTDIR    := $(BUILDDIR)/lst
DEPDIR    := $(BUILDDIR)/dep


COBJS := $(addprefix $(OBJDIR)/, $(notdir $(ALL_CSRC:.c=.c.o)))

ASMOBJS := $(addprefix $(OBJDIR)/, $(notdir $(ALL_ASM:.S=.S.o)))


SRCPATHS  := $(sort $(dir $(ALL_ASM)) $(dir $(ALL_CSRC)))

VPATH     = $(SRCPATHS)


OBJS := $(ASMOBJS) $(COBJS)


INCDIR := $(ALL_CINC)

IINCDIR   := $(patsubst %,-I%,$(INCDIR))


MCFLAGS   := -mcpu=$(MCU) -mthumb
ODFLAGS   = -D -x --syms
ASFLAGS   = $(MCFLAGS) $(OPT) -Wa,-amhls=$(LSTDIR)/$(notdir $(<:.S=.lst)) $(ADEFS)
CFLAGS    = $(MCFLAGS) $(OPT) $(COPT) $(CWARN) -Wa,-alms=$(LSTDIR)/$(notdir $(<:.c=.lst)) $(DEFS)
LDFLAGS   = $(MCFLAGS) $(OPT) -nostartfiles $(LLIBDIR) -Wl,-Map=$(BUILDDIR)/$(PROJECT).map,--cref,--no-warn-mismatch,--library-path=$(STARTUPLD),--script=$(LDSCRIPT)$(LDOPT)




CFLAGS   += -MD -MP -MF $(DEPDIR)/$(@F).d
ASFLAGS  += -MD -MP -MF $(DEPDIR)/$(@F).d

all:  $(OBJS) $(OUTFILES)

$(OBJS): | $(BUILDDIR) $(OBJDIR) $(LSTDIR) $(DEPDIR)

$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(LSTDIR):
	@mkdir -p $(LSTDIR)

$(DEPDIR):
	@mkdir -p $(DEPDIR)

$(COBJS) : $(OBJDIR)/%.c.o : %.c $(MAKEFILE_LIST)
	@echo Compiling $(<F)
	@$(CC) -c $(CFLAGS) -I. $(IINCDIR) $< -o $@

$(ASMOBJS) : $(OBJDIR)/%.S.o : %.S $(MAKEFILE_LIST)
	@echo Compiling $(<F)
	@$(AS) -c $(ASFLAGS) -I. $(IINCDIR) $< -o $@


$(BUILDDIR)/$(PROJECT).elf: $(OBJS) $(LDSCRIPT)
	@echo Linking $@
	@$(LD) $(OBJS) $(LDFLAGS) $(LIBS) -o $@

%.hex: %.elf
	@echo Creating $@
	@$(HEX) $< $@

%.bin: %.elf
	@echo Creating $@
	@$(BIN) $< $@

%.dmp: %.elf
	@echo Creating $@
	@$(OD) $(ODFLAGS) $< > $@
	@echo
	@$(SZ) $<

%.list: %.elf
	@echo Creating $@
	@$(OD) -S $< > $@
	@echo
	@echo Done

clean:
	@echo Cleaning..
	@rm -rf $(BUILDDIR)

-include $(wildcard $(DEPDIR)/*)



