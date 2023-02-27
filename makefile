ifeq ($(OS),Windows_NT)
	CC = g++
	EXT = .exe
	RM = del
else
	CC = g++
	EXT =
	RM = rm -f
endif

CFLAGS = -std=c++17 -Wall -O2
SOURCES = compiler.cpp lexer.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = application$(EXT)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS) $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)