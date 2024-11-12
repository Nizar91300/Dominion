# Compiler and Flags
CXX := clang++  # Utiliser g++ sur Linux
#WX_FLAGS := $(shell ./wxWidgets-3.2.6/wx-build/wx-config --cxxflags --libs)  # Chemin ajusté pour wxWidgets si nécessaire
CXXFLAGS := -std=c++17 -Wall $(WX_FLAGS) -Iinclude

# Directories
SRCDIR := src
OBJDIR := obj

# Files
SRCS := $(wildcard $(SRCDIR)/*.cpp) main.cpp
OBJS := $(patsubst %.cpp, $(OBJDIR)/%.o, $(notdir $(SRCS)))
TARGET := dominion

# Create object directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Rules
all: $(OBJDIR) $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(addprefix $(OBJDIR)/, $(notdir $(OBJS)))

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/main.o: main.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(TARGET)

clear:
	rm -rf $(OBJDIR) $(TARGET)

run:
	./dominion

# Phony targets
.PHONY: all clean clear run

