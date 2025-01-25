BIN_DIR := bin
SRC_DIR := src
INC_DIR := inc
OBJ_DIR := obj

TARGET := $(BIN_DIR)/libOpenWM.so

CFLAGS := -I$(INC_DIR) -Wall
ASFLAGS :=
LDFLAGS := -shared

objects = obj/context.o

all: $(objects) $(TARGET)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo "Compiling '$@'..."
	@$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(objects)
	@mkdir -p $(@D)
	@echo "Generating '$@'..."
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(objects)

.PHONY: clean
clean:
	@rm -rf $(objects) $(OBJ_DIR) $(TARGET) $(BIN_DIR)
