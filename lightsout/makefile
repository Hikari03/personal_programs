# stolen from https://gist.github.com/freelsn/fe5f160cf564e209dc9c5673296ee813

# - inc/
#     - *.h
# - src/
#     - *.c
#     - *.cpp
# - obj/
#     - *.o
# - main

TARGET := lightsout
SOURCES := $(wildcard *.c *.cpp)
OBJECTS := $(patsubst src%,obj%, $(patsubst %.c,%.o, $(patsubst %.cpp,%.o,$(SOURCES))))

INCLUDE := -I.
LIBPATH :=
LIBS := -lncursesw

FLAGS := -Wall
CCFLAGS := $(FLAGS) -std=c99
CXXFLAGS := $(FLAGS)

CC := gcc
CXX := g++

all: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(OBJECTS) -o $(TARGET) $(LIBPATH) $(LIBS)

%.o: %.c
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

.PHONY: clean help

clean_o:
	rm -rf *.o

clean_e:
	rm -f $(TARGET)