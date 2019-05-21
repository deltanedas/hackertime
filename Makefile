BUILDDIR = build
SOURCEDIR = src

CXX = g++-8
CXXFLAGS = -O3 -Wall -std=c++17 -I$(SOURCEDIR) -c -g
LDFLAGS = -L.

EXEC_FILE = hackertime
OBJ = hackertime.o
OBJECTS = $(patsubst %, $(BUILDDIR)/%, $(OBJ))

all: $(EXEC_FILE)

run: $(EXEC_FILE)
	./$(EXEC_FILE)

$(BUILDDIR)/%.o: $(SOURCEDIR)/%.cpp
	mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(EXEC_FILE): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf $(BUILDDIR)
	rm -f $(EXEC_FILE)

remake: clean $(EXEC_FILE)
