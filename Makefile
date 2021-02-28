# C++ Compiler
CXX := g++

# Flags
#   Compiler
CXXFLAGS += -c -g -Wall -std=c++11

#   Linker
LDFLAGS += -g

#   Library
LIBFLAGS :=
#
#   Include
INCLUDEFLAGS :=

# Program name
TARGET := main

# Test name
TESTTARGET := uitest

# Directories
#   Headers
HEADERDIR := include

#   Sources
SRCDIR := src

#   Objects
OBJDIR := obj

#   Binary
BINDIR := bin

################################################################################

HEADERS := $(wildcard $(HEADERDIR)/*.h)
SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(subst $(SRCDIR)/,$(OBJDIR)/,$(SRCS:.cpp=.o))

CXXFLAGS += $(INCLUDEFLAGS) -I$(HEADERDIR)
LDFLAGS += $(LIBFLAGS)

.PHONY: all test clean distclean

# Make main  binary
all: $(BINDIR)/$(TARGET)

# Compile object files together for main  binary
$(BINDIR)/$(TARGET): $(OBJS)
	mkdir -p $(BINDIR)
	$(CXX) $(LDFLAGS) $? -o $@


# Make test Binary
test: $(BINDIR)/$(TESTTARGET)

# Compile object files together for test binary
$(BINDIR)/$(TESTTARGET): $(OBJDIR)/$(TESTTARGET).o $(OBJDIR)/UI.o $(OBJDIR)/Move.o $(OBJDIR)/Board.o
	mkdir -p $(BINDIR)
	$(CXX) $(LDFLAGS) $^ -o $@

# Compile UI Test file in tests directory
$(OBJDIR)/$(TESTTARGET).o: tests/$(TESTTARGET).cpp
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $< -o $@

# Compile all other object files from source
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(OBJDIR)/*.o $(BINDIR)/$(TARGET)

distclean: clean