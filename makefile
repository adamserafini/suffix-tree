CXX := g++
CPP_FILES := $(filter-out src/js_bind.cpp, $(wildcard src/*.cpp))
OBJ_DIR := obj
OBJ_FILES := $(addprefix $(OBJ_DIR)/,$(notdir $(CPP_FILES:.cpp=.o)))
CC_FLAGS := -MMD

all: pre-build main

pre-build:
	mkdir -p $(OBJ_DIR)

main: $(OBJ_FILES)
	$(CXX) $(LD_FLAGS) -o $@ $^

obj/%.o: src/%.cpp
	$(CXX) $(CC_FLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR) main

-include $(OBJFILES:.o=.d)
