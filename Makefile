BINDIR = ./bin
TARGET = $(BINDIR)/$(shell basename `readlink -f .`)
SRCDIR = ./src
SOURCES = $(wildcard $(SRCDIR)/*.cxx)
OBJDIR = ./obj
OBJECTS = $(addprefix $(OBJDIR)/,$(notdir $(SOURCES:.cxx=.o)))
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -O2 -march=native

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	-mkdir -p $(BINDIR)
	$(CXX) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cxx
	-mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -Rf $(OBJDIR) $(BINDIR)
