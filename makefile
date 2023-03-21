.PHONY: default all clean

CXX			=	g++
CXXFLAGS	=	-std=c++11 -g

BUILD_DIR	=	build
BIN_DIR 	=	$(BUILD_DIR)/bin
SRC_DIR		=	src

CLIENT_TARGET		=	scheduler
CLIENT_EXEC			=	$(BUILD_DIR)/bin/$(CLIENT_TARGET)
CLIENT_SOURCES		=	$(wildcard src/*.cpp)
CLIENT_OBJECTS		=	$(CLIENT_SOURCES:src/%.cpp=$(BUILD_DIR)/%.o)

$(BUILD_DIR):
	mkdir -p $@
	mkdir -p $(BIN_DIR)

$(CLIENT_OBJECTS): $(CLIENT_SOURCES) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ -c $^

$(CLIENT_TARGET): $(CLIENT_OBJECTS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $(CLIENT_EXEC)

all: $(CLIENT_TARGET) $(LIB_TARGET)

clean:
	rm -rf ./$(BUILD_DIR)

default: all