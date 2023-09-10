OUTPUT := kernel.bin
OUTPUT_ISO := kernel.iso

AS=i686-elf-as
CC=i686-elf-gcc
RM=rm -rf

CC_FLAGS=-std=gnu99 -ffreestanding -O3 -Wall -Wextra
CC_HEADERS_FLAGS=-Iinclude/

OBJ_AS :=
OBJ_C :=

HEADERS := $(wildcard include/*.h)

clean-files-list := *.bin *.o *.iso iso/
LD_LINKER := kernel/linker.ld

define resolve_path
	OBJ_AS += $(addprefix $(CURRENT_DIR), $(OBJS_AS))
	OBJ_C += $(addprefix $(CURRENT_DIR), $(OBJS_C))
	clean-files-list += $(addprefix $(CURRENT_DIR), $(clean-files))
endef

include kernel/Makefile.mk

.PHONY: all
all: iso/boot/$(OUTPUT)

clean:
	$(RM) $(clean-files-list)

$(OBJ_AS):%.o:%.s
	$(AS) $< -o $@

$(OBJ_C):%.o:%.c $(HEADERS)
	$(CC) -c $< -o $@ $(CC_FLAGS) $(CC_HEADERS_FLAGS)

iso/boot/$(OUTPUT): $(OBJ_AS) $(OBJ_C) $(LD_LINKER)
	mkdir -p iso/boot/grub
	echo "if grub-file --is-x86-multiboot $(OUTPUT); then\n\techo multiboot confirmed\nelse\n\techo the file is not multiboot\nfi\n" > iso/boot/grub/grub.cfg
	echo "menuentry \"myos\" {\n\tmultiboot /boot/$(OUTPUT)\n}" >> iso/boot/grub/grub.cfg
	$(CC) -T $(LD_LINKER) -o iso/boot/$(OUTPUT) -ffreestanding -O2 -nostdlib $(OBJ_AS) $(OBJ_C) -lgcc
	grub-mkrescue -o $(OUTPUT_ISO) iso
