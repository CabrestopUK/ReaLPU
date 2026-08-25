# 		Compiler and flags  
CXX =g++ # 					compiler
CFLAGS =-Wall -Wextra -g # 	compiler flags 
CFLAGS +=-MMD -MP # 		-MMD -MP for dependency generation  
LDFLAGS =#					linker flags
 
# 		Directories  
SRC_DIR =src# 				source .cpp and .h
INCLUDE_DIR =include# 		project wide include path
BUILD_DIR =build# 			build path
BIN_DIR =bin# 				(below)
TARGET =$(BIN_DIR)/main# 	(where the .exe will go)
 
# 		Include paths  
INCLUDES = -I$(INCLUDE_DIR) -I$(SRC_DIR)
 
# 		Find all .cpp files  
SOURCES := $(shell find $(SRC_DIR) -name '*.cpp')  
 
#		Generate object file paths  
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))  
 
# 		Auto-generated dependency files  
DEPS := $(OBJECTS:.o=.d)  
 
# 		Phony targets  
.PHONY: all clean  
 
# 		Default target  
all: $(TARGET)  
 
# 		Build executable  
$(TARGET): $(OBJECTS)  
	@mkdir -p $(BIN_DIR)  
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $(TARGET)  
	@echo "Built target: $@"  
 
# 		Compile .cpp to .o  
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp  
	@mkdir -p $(@D)  
	$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@  
 
# 		Clean artifacts  
clean:  
	@rm -rf $(BUILD_DIR) $(BIN_DIR)  
	@echo "Cleaned build and bin directories"  
 
# 		Include dependencies  
-include $(DEPS)  