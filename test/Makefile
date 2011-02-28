COMPILER=g++
CFLAGS=-Wall -w -pedantic -g

UNITS=units/point.class.test.o ../src/geometry/point.h
TEST_LIB=unit.o
OUTPUT_NAME=unittests
MAIN=unittests.o

.PHONY: all clean

# For linux only, not supported on FreeBSD
%.o: %.cpp
	$(COMPILER) $(CFLAGS) -c $(<) -o $(@)
units/%.o: units/%.h
	$(COMPILER) $(CFLAGS) -c $(<) -o $(@)


all: $(UNITS) $(TEST_LIB) $(MAIN)
	$(COMPILER) $(CFLAGS) -o $(OUTPUT_NAME) $(UNITS) $(TEST_LIB) $(MAIN)

clean:
	rm -rf $(OUTPUT_NAME) *~ *.o
