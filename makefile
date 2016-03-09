# Compiler
CC      = clang++
CFLAGS  = -std=c++11 -Wall -Wpedantic
LIBS    = 

# Source directories (see GNU make VPATH)
VPATH = src

# Directories
BIN_DIR = bin
OBJ_DIR = obj

SRC = Floor.h Graph.h Room.h

OBJ = main.o Floor.o Graph.o Room.o

GEN = $(addprefix $(BIN_DIR)/, generator)


.DEFAULT_GOAL := all


$(OBJ_DIR)/%.o: %.cpp $(SRC)
	$(CC) $(CFLAGS) -c -o $@ $<

$(GEN): $(addprefix $(OBJ_DIR)/, $(OBJ))
	$(CC) $(LIBS) -o $@ $^ 

.PHONY: all
all: directories $(GEN)

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: directories
directories:
	@mkdir -p {$(BIN_DIR),$(OBJ_DIR)}

.PHONY: debug
debug: CFLAGS += -DDEBUG -g -O0 -v
debug: all

.PHONY: release
release: CFLAGS += -O2
release: all

.PHONY: extreme
extreme: CFLAGS += -O3
extreme: all
