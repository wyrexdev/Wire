# =========================
# COMPILER / TOOLS
# =========================
CXX := g++
CC  := gcc
AR  := ar

# =========================
# FLAGS
# =========================
CXXFLAGS := -std=c++20 -O2 -Wall -Wextra -Iinclude
CFLAGS   := -O2 -Wall -Wextra -Iinclude
LDFLAGS  := -lssl -lcrypto -lz

# =========================
# DIRECTORIES
# =========================
SRC_DIR   := src
INC_DIR   := include
BUILD_DIR := build

# =========================
# INSTALL PATHS
# =========================
PREFIX ?= /usr/local
LIBDIR := $(PREFIX)/lib
INCDIR := $(PREFIX)/include/Wire
BINDIR := $(PREFIX)/bin

# =========================
# TARGET NAMES
# =========================
BIN_NAME   := Wire
LIB_NAME   := wire
LIB_STATIC := lib$(LIB_NAME).a

# =========================
# SOURCES
# =========================
CPP_SRCS := $(shell find $(SRC_DIR) -type f -name '*.cpp')
C_SRCS   := $(shell find $(SRC_DIR) -type f -name '*.c')

# main.cpp lib'e girmesin
LIB_CPP_SRCS := $(filter-out $(SRC_DIR)/main.cpp, $(CPP_SRCS))

# =========================
# OBJECTS
# =========================
LIB_OBJS := $(LIB_CPP_SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o) \
            $(C_SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

MAIN_OBJ := $(BUILD_DIR)/main.o

# =========================
# DEFAULT TARGET
# =========================
all: $(LIB_STATIC) $(BIN_NAME)

# =========================
# STATIC LIBRARY
# =========================
$(LIB_STATIC): $(LIB_OBJS)
	@echo "AR  $@"
	@$(AR) rcs $@ $^

# =========================
# CLI BINARY
# =========================
$(BIN_NAME): $(LIB_STATIC) $(MAIN_OBJ)
	@echo "LINK $@"
	@$(CXX) $(MAIN_OBJ) -L. -l$(LIB_NAME) -o $@ $(LDFLAGS)

# =========================
# C++ COMPILE
# =========================
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo "CXX $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# =========================
# C COMPILE
# =========================
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "CC  $<"
	@$(CC) $(CFLAGS) -c $< -o $@

# =========================
# INSTALL (AUTO HEADER NAMESPACE)
# =========================
install: all
	@echo "Installing Wire..."

	@install -d $(DESTDIR)$(LIBDIR)
	@install -m 644 $(LIB_STATIC) $(DESTDIR)$(LIBDIR)

	# headers -> /usr/local/include/Wire/*
	@install -d $(DESTDIR)$(INCDIR)
	@cp -r $(INC_DIR)/* $(DESTDIR)$(INCDIR)

	@install -d $(DESTDIR)$(BINDIR)
	@install -m 755 $(BIN_NAME) $(DESTDIR)$(BINDIR)

	@echo "Updating linker cache"
	@ldconfig

# =========================
# UNINSTALL
# =========================
uninstall:
	@echo "Uninstalling Wire..."

	@rm -f $(LIBDIR)/$(LIB_STATIC)
	@rm -rf $(INCDIR)
	@rm -f $(BINDIR)/$(BIN_NAME)

	@ldconfig

# =========================
# CLEAN
# =========================
clean:
	@echo "Cleaning"
	@rm -rf $(BUILD_DIR) $(BIN_NAME) $(LIB_STATIC)

# =========================
# PHONY
# =========================
.PHONY: all clean install uninstall
