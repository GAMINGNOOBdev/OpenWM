BIN_DIR := bin
SRC_DIR := src
INC_DIR := inc
OBJ_DIR := obj

TARGET := $(BIN_DIR)/libFrostedWM.so

CFLAGS := \
	-I$(INC_DIR) -fPIC
LDFLAGS := \
    -nostdlib \
    -shared \
    -z max-page-size=0x1000

CFILES := $(shell find -L src -type f -name '*.c')

CFILES := $(subst src/,,$(CFILES))

objects = $(addprefix obj/,$(CFILES:.c=.o))

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
