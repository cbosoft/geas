CC = g++
BUILDTYPE = release
USER_DEFINES =
CFLAGS = -Wall -Wextra -Werror -g -std=c++17 $(USER_DEFINES) $(DEFS)
LINK = -I/usr/local/include `pkg-config --libs glfw3` `pkg-config --static --libs glfw3` `pkg-config --libs glew` -lpthread -lopenal -lsqlite3

HDR = $(shell find src -name '*.hpp')
SRC = $(shell find src -name '*.cpp')
OBJ_WD = $(SRC:.cpp=.o)
OBJ = $(subst src,obj,$(OBJ_WD))

## Colours
COL_OBJ = $(shell tput setaf 3 2>/dev/null)
COL_EXE = $(shell tput setaf 4 2>/dev/null)
COL_SO = $(shell tput setaf 5 2>/dev/null)
COL_RST = $(shell tput sgr0 2>/dev/null)
COL_BLD = $(shell tput bold 2>/dev/null)

DEFS     :=
ifeq ($(OS),Windows_NT)
 DEFS +=  -DWINDOWS
else
 UNAME_S := $(shell uname -s)
 ifeq ($(UNAME_S),Linux)
  DEFS +=  -DLINUX
 else
  DEFS +=  -DMACOS
	DEFS +=  -DGL_SILENCE_DEPRECIATION
 endif
endif

DATE = $(shell date +"%Y-%m-%d")
ARCH = $(shell gcc -dumpmachine)

DEFS += -DDATE=\"$(DATE)\"
DEFS += -DARCH=\"$(ARCH)\"

.PHONY: all options debug

all: geas

debug:
	@$(MAKE) USER_DEFINES="-DDEBUG" BUILDTYPE="debug"

options:
	@echo "Compiling on $(DATE) for $(ARCH) ($(BUILDTYPE) version)"

geas: options $(OBJ) $(HDR)
	@printf "$(COL_OBJ)LINKING OBJECTS TO EXECUTABLE $@$(COL_RST)\n"
	@$(CC) $(CFLAGS) $(OBJ) -o $@ $(LINK)

obj/%.o: src/%.cpp $(HDR)
	@printf "$(COL_OBJ)ASSEMBLING OBJECT $@$(COL_RST)\n"
	@mkdir -p `dirname $@`
	@$(CC) $(CFLAGS) -c $< -o $@ -DGL_SILENCE_DEPRECATION

clean:
	rm -rf obj/* geas
