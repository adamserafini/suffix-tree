CPP_FILES := $(wildcard src/*.cpp)
OBJ_DIR := obj
OBJ_FILES := $(addprefix $(OBJ_DIR)/,$(notdir $(CPP_FILES:.cpp=.o)))
CC_FLAGS := -MMD

all: pre-build main

pre-build:
	mkdir -p $(OBJ_DIR)

main: $(OBJ_FILES)
	g++ $(LD_FLAGS) -o $@ $^

obj/%.o: src/%.cpp
	g++ $(CC_FLAGS) -c -o $@ $<

-include $(OBJFILES:.o=.d)
