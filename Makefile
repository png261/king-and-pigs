# Includes the config.mk configurations
include config.mk

# Default shell
SHELL = bash

# %.o file names
NAMES = $(notdir $(basename $(wildcard $(SRC_DIR)/*.$(SRCEXT))))
OBJECTS =$(patsubst %,$(LIB_DIR)/%.o,$(NAMES))

#
# COMPILATION RULES
#

default: all

# Rule for link and generate the binary file
all: $(OBJECTS) 
	@echo -en "LD ";
	$(CC) -o $(BIN_DIR)/$(BINARY) $+ $(DEBUG) $(CFLAGS) $(LIBS)
	@echo -en "\n--\nBinary file placed at" \
			  "$(BIN_DIR)/$(BINARY)\n";


# Rule for object binaries compilation
$(LIB_DIR)/%.o: $(SRC_DIR)/%.$(SRCEXT)
	@echo -en "CC ";
	$(CC) -c $^ -o $@ $(DEBUG) $(CFLAGS) $(LIBS)

# Run
FILES = $(filter-out $@,$(MAKECMDGOALS))
run:
	$(BIN_DIR)/$(BINARY) $(FILES)

# debug
debug:
	gdb $(BIN_DIR)/$(BINARY) $(FILES)

# Clean
clean:
	@rm -rvf $(BIN_DIR)/* $(LIB_DIR)/* $(LOG_DIR)/*;

# Help
help:
	@echo "$(PROJECT_NAME)"
	@echo
	@echo "Target rules:"
	@echo "    all          - Compiles and generates binary file"
	@echo "    run          - Run binary file"
	@echo "    clean        - Clean the project by removing binaries"
	@echo "    help         - Prints a help message with target rules"
