PROJECT_NAME = prm
SRC_DIR = src
BUILD_DIR = build

SRC = $(wildcard $(SRC_DIR)/*.cpp)
HEADERS = $(wildcard include/prm/*.hpp)

TARGET = $(BUILD_DIR)/$(PROJECT_NAME)

CXX_FLAGS = -Iinclude -std=c++17

$(TARGET): $(SRC) $(HEADERS)
	@ mkdir -p $(BUILD_DIR)
	$(CXX) -o $@ $(SRC) $(CXX_FLAGS)

dev: $(TARGET)
	@ cp $^ .