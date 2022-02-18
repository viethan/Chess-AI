CXX = g++ -std=c++11
CXXFLAGS = -Wall -O -g -fsanitize=leak 
LIBFLAGS = -w -lSDL2 -lSDL2_image

SRCDIR = src
PIECESDIR = src/pieces
OBJDIR = obj
BINDIR = bin

SOURCES = $(wildcard $(SRCDIR)/*.cpp $(PIECESDIR)/*.cpp)  # list of all .cpp files in the src directory

TARGET=chess

$(BINDIR)/$(TARGET):
	$(CXX) $(CXXFLAGS) $(SOURCES) $(LIBFLAGS) -o $(BINDIR)/$(TARGET)  

.PHONY: clean
clean:
	rm  -f $(BINDIR)/$(TARGET)
