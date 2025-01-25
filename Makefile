BIN_DIR := bin
SRC_DIR := src
INC_DIR := inc
OBJ_DIR := obj

TARGET := $(BIN_DIR)/libFrostedWM.bin

CFLAGS := -I$(INC_DIR)
ASFLAGS :=
LDFLAGS := -T ./linker.ld

CFILES := $(shell find -L src -type f -name '*.c')
ASFILES := $(shell find -L src -type f -name '*.S')
NASMFILES := $(shell find -L src -type f -name '*.asm')

CFILES := $(subst src/,,$(CFILES))
ASFILES := $(subst src/,,$(ASFILES))
NASMFILES := $(subst src/,,$(NASMFILES))

objects = $(addprefix obj/,$(CFILES:.c=.o) $(ASFILES:.S=.o) $(NASMFILES:.asm=.o))

all: $(objects) $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo "Compiling '$@'..."
	@$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(objects)
	@mkdir -p $(@D)
	@echo "Generating '$@'..."
	@$(LD) $(CFLAGS) $(LDFLAGS) -o $@ $(objects)

.PHONY: clean
clean:
	@rm -rf $(objects) $(OBJ_DIR) $(TARGET) $(BIN_DIR)
