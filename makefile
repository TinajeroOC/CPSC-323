CC = g++
CFLAGS = -std=c++17 -Wall -O2
SOURCES = compiler.cpp lexer.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = code.out

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)