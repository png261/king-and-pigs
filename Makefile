# Includes the config.mk igurations
include config.mk

#
# Validating project variables defined in config.mk
#

# Gets the Operating system name
OS = $(shell uname -s)

# Default shell
SHELL = bash

# Color prefix for Linux distributions
COLOR_PREFIX = e

ifeq ($(OS),Darwin)
	COLOR_PREFIX = 033
endif

# Color definition for print purpose
BROWN=\$(COLOR_PREFIX)[0;33m
BLUE=\$(COLOR_PREFIX)[1;34m
END_COLOR=\$(COLOR_PREFIX)[0m

# %.o file names
NAMES = $(notdir $(basename $(wildcard $(SRCDIR)/*.$(SRCEXT))))
OBJECTS =$(patsubst %,$(LIBDIR)/%.o,$(NAMES))

#
# COMPILATION RULES
#

default: all

# Rule for link and generate the binary file
all: $(OBJECTS) 
	@echo -en "$(BROWN)LD $(END_COLOR)";
	$(CC) -o $(BINDIR)/$(BINARY) $+ $(DEBUG) $(CFLAGS) $(LIBS)
	@echo -en "\n--\nBinary file placed at" \
			  "$(BROWN)$(BINDIR)/$(BINARY)$(END_COLOR)\n";


# Rule for object binaries compilation
$(LIBDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo -en "$(BROWN)CC $(END_COLOR)";
	$(CC) -c $^ -o $@ $(DEBUG) $(CFLAGS) $(LIBS)

# Run
FILES = $(filter-out $@,$(MAKECMDGOALS))
run:
	$(BINDIR)/$(BINARY) $(FILES)

# debug
debug:
	gdb $(BINDIR)/$(BINARY) $(FILES)

# Clean
clean:
	@rm -rvf $(BINDIR)/* $(LIBDIR)/* $(LOGDIR)/*;

# Install
install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f $(BINDIR)/$(BINARY) ${DESTDIR}${PREFIX}/bin/$(PROJECT_NAME)
	chmod 755 ${DESTDIR}${PREFIX}/bin/$(PROJECT_NAME)
	@echo -en "$(BROWN)-- YAH! $(PROJECT_NAME) HAS BEEN INSTALLED! --$(END_COLOR)\n"

# Uninstall
uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/$(PROJECT_NAME)
	@echo -en "$(BROWN)-- UNINSTALLED $(PROJECT_NAME)! --$(END_COLOR)\n"

# Help
help:
	@echo "$(PROJECT_NAME)"
	@echo
	@echo "Target rules:"
	@echo "    all          - Compiles and generates binary file"
	@echo "    install      - Compiles and install binary file"
	@echo "    uninstall    - uninstall binary file"
	@echo "    run          - run binary file"
	@echo "    clean        - Clean the project by removing binaries"
	@echo "    help         - Prints a help message with target rules"
