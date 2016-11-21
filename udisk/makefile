# JetOS makefile

CC	:= sparc-elf-gcc
OBJDUMP := sparc-elf-objdump

CFLAGS1	:= -O2 -msoft-float -Tlinkprom -N -L./ -nostdlib -I./inc/ -I./inc/crypt/
CFLAGS2	:= -O2 -msoft-float -I./inc/ -I./inc/crypt/
OBJECTS := init0.o lb1spc.o lb2spc.o lb3spc.o main.o eflash.o vsprintf.o jtag_con.o mem.o ahb_usbnfc.o nflash.o usb.o 

OBJ	:= $(foreach temp, $(OBJECTS), ./out/obj/$(temp))

.PHONY: build clean tcm

./out/udisk.elf	: $(OBJ)
	@$(CC) $(CFLAGS1) -o $@ $(OBJ)
	@$(OBJDUMP) -d $@ > ./out/1
	@$(OBJDUMP) -t $@ > ./out/2
	@$(OBJDUMP) -g $@ > ./out/3
	@echo $@ build done.
	

./out/obj/%.o		: ./asm/%.S
	@mkdir -p ./out/obj
	$(CC) -c $(CFLAGS2) -o $@ $<
./out/obj/%.o		: ./src/%.c	
	@mkdir -p ./out/obj
	$(CC) -c $(CFLAGS2) -o $@ $<
./out/obj/%.o		: ./src/crypt/%.c	
	$(CC) -c $(CFLAGS2) -o $@ $<
	
	

clean		:
	@rm -rf ./out/*


