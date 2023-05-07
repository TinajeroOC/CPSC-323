ifeq ($(OS),Windows_NT)
	CC = g++
	EXT = .exe
	RM = del
	SEP = \\
else
	CC = g++
	EXT =
	RM = rm -f
	SEP = /
endif

CFLAGS = -std=c++17 -Wall -c -g -static -static-libgcc -static-libstdc++
SOURCES = src$(SEP)main.cpp src$(SEP)compiler$(SEP)token.cpp src$(SEP)compiler$(SEP)compiler.cpp src$(SEP)compiler$(SEP)lexer.cpp src$(SEP)compiler$(SEP)parser.cpp src$(SEP)compiler$(SEP)ocg.cpp
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