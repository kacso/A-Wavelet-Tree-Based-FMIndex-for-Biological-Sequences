PROJECT = FMIndex
SOURCE = $(wildcard src/*.cpp)
HEADERS =$(wildcard include/*.h)

IDIR = ./include
CC = g++
CXXFLAGS = -std=c++11 -w -I$(IDIR)
LDFLAGS = 
OBJECTS = ${SOURCE:.cpp=.o}

$(PROJECT): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(PROJECT)

clean:
	-rm -f $(PROJECT) $(OBJECTS) *.core
