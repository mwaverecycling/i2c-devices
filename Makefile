CC = gcc
OS = $(shell uname -s)



SRC_DIR = ./src
INC_DIR = ./include
INC_DIR_HACK = ./hack_include
TEST_DIR = ./test

SO_NAME = i2cdevices
LIB_NAME = lib$(SO_NAME)

BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/objects

TESTFILE = $(TEST_DIR)/test.c
TARGET_TEST = $(BUILD_DIR)/i2ctest
TARGET_LIB = $(BUILD_DIR)/$(LIB_NAME)

SOURCES = $(shell find $(SRC_DIR) -type f -name *.c)
HEADERS = $(shell find $(INC_DIR) -type f -name *.h)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

INSTALL_LOC = /usr/local
INSTALL_LIB_LOC = $(INSTALL_LOC)/lib
INSTALL_INC_LOC = $(INSTALL_LOC)/include


INC_FLAGS = -I$(SRC_DIR) -I$(INC_DIR)
ifeq ($(OS),Darwin)
	INC_FLAGS += -I$(INC_DIR_HACK)
endif

build: $(OBJECTS) $(HEADERS)
	@echo $(OBJECTS)

lib_shared: build
	$(CC) -shared -fpic -Wl,-soname,$(LIB_NAME).so -o $(TARGET_LIB).so $(OBJECTS)
lib: build
	ar rcs $(TARGET_LIB).a $(OBJECTS)

build_test: lib
	$(CC) -o $(TARGET_TEST) $(TESTFILE) $(TARGET_LIB).a
build_test_shared: lib_shared
	$(CC) -o $(TARGET_TEST) $(TESTFILE) -l$(SO_NAME)
	


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) -fpic $(INC_FLAGS) -c $< -o $@

test: build_test
	$(TARGET_TEST)
test_shared: build_test_shared
	export LD_LIBRARY_PATH=$(INSTALL_LIB_LOC)
	$(TARGET_TEST)

install: lib
install_shared: lib
	cp $(TARGET_LIB).* $(INSTALL_LIB_LOC)
	cp -rt $(INSTALL_INC_LOC) $(wildcard $(INC_DIR)/*)
uninstall:
	rm -f $(INSTALL_LIB_LOC)/$(LIB_NAME).*
	rm -f $(patsubst $(INC_DIR)/%, $(INSTALL_INC_LOC)/%, $(HEADERS))
	rm -fd $(INSTALL_INC_LOC)/$(shell ls -d $(INC_DIR)/*/ | cut -d"/" -f3-)

info:
	@echo $(SOURCES)
	@echo $(OBJECTS)
	@echo $(HEADERS)

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(TARGET_LIB).*
	rm -f $(TARGET_TEST)

