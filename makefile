
CXX			=	g++
CXXFLAGS	=	-std=c++11

BIN_DIR 	=	bin

SIM_TARGET	=	$(BUILD_DIR)/simulator.so
SIM_SOURCES	=	simulator/src/$(wildcard *.cpp)
SIM_OBJECTS	=	$(SIM_SOURCES:.cpp=.o)
SIM_INCLUDE	=	simulator/include/$(wildcard *.hpp)

APP_TARGET	=	scheduler_app
APP_EXEC	=	$(BIN_DIR)/$(APP_TARGET)
APP_SOURCES	=	$(wildcard $(APP_TARGET)/src/*.cpp)
APP_OBJECTS	=	$(APP_SOURCES:$(APP_TARGET)/src/%.cpp=$(APP_TARGET)/obj/%.o)
APP_OBJ_DIR	=	$(APP_TARGET)/obj

.PHONY: all clean

$(BIN_DIR):
	mkdir -p $@

$(APP_OBJ_DIR):
	mkdir -p $@

$(APP_OBJECTS): $(APP_SOURCES) | $(APP_OBJ_DIR)
	$(CXX) $(CXXFLAGS) -o $@ -c $^

$(APP_TARGET): $(APP_OBJECTS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $(APP_EXEC)

all: $(APP_TARGET)

clean:
	rm -rf ./$(BIN_DIR)/*
	rm -rf ./$(APP_OBJ_DIR)/*