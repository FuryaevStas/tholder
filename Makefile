TARGET=holder
PREFIX=/usr/local/bin

BINARIES=./bins

CFLAGS=-c -Wall
LDFLAGS=
COUTPUT=$(TARGET)

SRC=$(wildcard *.cpp)

.PHONY: all clean install uninstall

all: $(SRC:.cpp=.o)
	g++ $(LDFLAGS) $(addprefix $(BINARIES)/, $(SRC:.cpp=.o)) -o $(COUTPUT)

.cpp.o:
	g++ $(CFLAGS) $< -o $(BINARIES)/$@
	
install:

uninstall:

clean:
	rm -rf ./*/*.o $(COUTPUT)