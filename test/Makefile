COMPILER=g++
CFLAGS=-Wall -w -pedantic -g

UNITS=units/
OUTPUT_NAME=unittests
MAIN=unittests.o

.PHONY: all clean

# For linux only, not supported on FreeBSD
#%.o: %.cpp
#       $(COMPILER) $(CFLAGS) -c $(<) -o $(@)

all: $(UNITS) $(MAIN)
        $(COMPILER) $(CFLAGS) -o $(OUTPUT_NAME) $(UNITS) $(MAIN)

clean:
        rm -rf $(OUTPUT_NAME) *~ *.o
