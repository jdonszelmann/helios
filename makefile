CC = g++
CFLAGS = -std=c++11 -c
LDFLAGS = 
SOURCES = compile.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = Helios


all:$(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS)
	rm $(EXECUTABLE) 