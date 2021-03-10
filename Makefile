CXX = g++
CXXFLAGS = -Wall

SRCDIR = src
INCLUDEDIR = include
BINDIR = bin
LIBSDIR = lib/Windows

LIBS = sfml-graphics-2 sfml-window-2 sfml-system-2 sfml-audio-2

CXXFLAGS += -I$(INCLUDEDIR)

SRCFILES = $(wildcard $(SRCDIR)/*.cpp)
OBJFILES = $(SRCFILES:$(SRCDIR)/%.cpp=$(BINDIR)/%.o)
HEADERFILES = $(wildcard $(SRCDIR)/*.h)
EXE = $(BINDIR)/snake

RMQUIET = del /Q
MKDIR = mkdir

all: $(EXE)

debug: CXXFLAGS += -O0 -g
debug: $(EXE)

release: CXXFLAGS += -O3
release: $(EXE)

$(EXE): $(BINDIR) $(OBJFILES) $(HEADERFILES)
	$(CXX) $(CXXFLAGS) -L$(LIBSDIR) $(addprefix -l,$(LIBS)) -o $(EXE) $(OBJFILES)

$(BINDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERFILES)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BINDIR):
	$(MKDIR) $@

clean:
	$(RMQUIET) $(BINDIR)\*.o
	$(RMQUIET) $(BINDIR)\snake.exe

rebuild: clean all

.PHONY: all debug release clean rebuild