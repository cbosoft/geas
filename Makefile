CC = g++
CFLAGS = -Wall -Wextra -Werror -g -std=c++17
LINK = -I/usr/local/include `pkg-config --libs glfw3` `pkg-config --static --libs glfw3` `pkg-config --libs glew`

SRC = $(shell ls src/*.cpp src/**/*.cpp)
OBJ = $(SRC:.cpp=.o)

## Colours
COL_OBJ = $(shell tput setaf 3 2>/dev/null)
COL_EXE = $(shell tput setaf 4 2>/dev/null)
COL_SO = $(shell tput setaf 5 2>/dev/null)
COL_RST = $(shell tput sgr0 2>/dev/null)
COL_BLD = $(shell tput bold 2>/dev/null)

.PHONY: all options

all: options geas

options:
	@echo $(SRC)

geas: $(OBJ) $(HDR)
	@printf "$(COL_OBJ)LINKING OBJECTS TO EXECUTABLE $@$(COL_RST)\n"
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LINK) -DGL_SILENCE_DEPRECATION

obj/%.o: src/%.cpp $(HDR)
	@printf "$(COL_OBJ)ASSEMBLING OBJECT $@$(COL_RST)\n"
	@mkdir -p `dirname $@`
	@$(CC) $(CFLAGS) -c $< -o $@ -DGL_SILENCE_DEPRECATION

clean:
	rm -rf obj/* geas
