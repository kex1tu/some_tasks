CC=clang++
CFLAGS=-c -pedantic-errors -gdwarf-4 -std=c++20
LDFLAGS=
SOURCES=stockexchange.cpp database.cpp datetime.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=stockexchange

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
