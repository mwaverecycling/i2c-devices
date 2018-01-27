CC = gcc
OS = $(shell uname -s)

SRC_DIR = ./src
INC_DIR = ./include
INC_DIR_HACK = ./hack_include
BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/objects
TARGET = $(BUILD_DIR)/libi2cdevices

SOURCES = $(shell find $(SRC_DIR) -type f -name *.c)
HEADERS = $(shell find $(SRC_DIR) -type f -name *.h)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

INC_FLAGS = -I$(SRC_DIR) -I$(INC_DIR)
ifeq ($(OS),Darwin)
	INC_FLAGS += -I$(INC_DIR_HACK)
endif

build: $(OBJECTS) $(HEADERS)
	@echo $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(INC_FLAGS) -c $< -o $@

run: build
	$(TARGET)

info:
	@echo $(SOURCES)
	@echo $(OBJECTS)

clean:
	rm -rf $(OBJ_DIR)
	rm $(TARGET)