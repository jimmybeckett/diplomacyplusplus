CC=g++
CFLAGS=-Wall -Werror -g -std=c++11
OUTFILE=dip.out
SOURCEFILES=$(shell find . -type f -name "*.cpp")
HEADERS=$(shell find . -type f -name "*.h")
OBJECTS=$(addsuffix .o, $(basename $(SOURCEFILES)))

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(OUTFILE)

clean:
	rm -f $(OBJECTS)
	rm -f $(OUTFILE)
