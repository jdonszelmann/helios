CC = g++
CFLAGS = -std=c++11 -c
LDFLAGS = 
SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = Helios


all:$(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

run:$(SOURCES) $(EXECUTABLE)
	./Helios test.hel

go:
	./Helios test.hel
	
clean:
	rm $(OBJECTS)
	rm $(EXECUTABLE) 