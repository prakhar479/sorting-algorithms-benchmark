# Compiler
CC := gcc

# Compiler flags
CFLAGS := -Wall -Wextra -g

# Source directory
SRC_DIR := sorting_routines

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.c) main.c

# Object directory
OBJ_DIR := obj

# Object files
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(filter %.c,$(SRCS)))

# Output executable
TARGET := benchmark

# Analytics file
ANALYTICS := analytics.py
OUTPUT := output.txt
MAX_SIZE := 10000
MAX_ITTER := 100
STEP_SIZE := 100

# Results
RESULT_DIR := results

ifdef MAX_INPUT_SIZE
 	MAX_SIZE := $(MAX_INPUT_SIZE)
endif

ifdef MAX_ITTERATIONS
 	MAX_ITTER := $(MAX_ITTERATIONS)
endif

ifdef STEP
 	STEP_SIZE := $(STEP)
endif

# Default target
all: objdir $(TARGET)

# Create obj directory
objdir:
	mkdir -p $(OBJ_DIR)

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files into executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Compile the project and redirect the output to a txt file and Run the Analytics
results: all
	touch $(OUTPUT); \
	for i in $$(seq 1 $(STEP_SIZE) $(MAX_SIZE)); do \
		echo "Run $$i start" >> $(OUTPUT); \
		./$(TARGET) $$i ${MAX_ITTER} >> $(OUTPUT); \
		echo "Run $$i end" >> $(OUTPUT); \
	done; \
	mkdir -p $(RESULT_DIR); \
	python3 $(ANALYTICS) $(OUTPUT); \

# Clean the project
clean:
	rm -rf $(OBJ_DIR) $(TARGET) $(OUTPUT)

clean-results:
	rm -rf $(RESULT_DIR)

clean-all: clean clean-results
