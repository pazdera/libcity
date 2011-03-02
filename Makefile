COMPILER=g++
COMPILER_FLAGS=-Wall -fPIC -pedantic -g

ARCHIVER=ar
ARCHIVER_FLAGS=rcs

LIB_FILENAME=libcity
TEST_FILENAME=libcity_test

.PHONY: install uninstall static dynamic clean doc test

all: static dynamic

# LIB Object files and sources ##########################

# Geometry package
GEOMETRY_PACKAGE=src/geometry/curve.o \
                 src/geometry/line.o \
                 src/geometry/point.o

# Streetgraph package
STREETGRAPH_PACKAGE=src/streetgraph/zone.o \
                    src/streetgraph/intersection.o \
                    src/streetgraph/road.o \
                    src/streetgraph/primaryroad.o \
                    src/streetgraph/secondaryroad.o \
                    src/streetgraph/streetgraph.o

LIB_OBJECTS=$(GEOMETRY_PACKAGE) $(STREETGRAPH_PACKAGE)

$(LIB_OBJECTS): %.o: %.cpp
	$(COMPILER) $(COMPILER_FLAGS) -c $< -o $@



# TEST Object files and sources ##########################

# Unit tests
TEST_UNITS=test/units/point.class.test.o

TEST_MAIN=test/main.o
TEST_OBJECTS=test/unit.o $(TEST_UNITS) $(TEST_MAIN)

$(TEST_OBJECTS): %.o: %.cpp
	$(COMPILER) $(COMPILER_FLAGS) -c $< -o $@

static: $(LIB_OBJECTS)
	$(ARCHIVER) $(ARCHIVER_FLAGS) $(LIB_FILENAME).a $(LIB_OBJECTS)

dynamic: $(LIB_OBJECTS)
	$(COMPILER) -shared -o $(LIB_FILENAME).so $(LIB_OBJECTS)

install:
	

uninstall:
	

test: $(TEST_OBJECTS) static
	$(COMPILER) $(COMPILER_FLAGS) -static -L. -lcity -o $(TEST_FILENAME) $(TEST_OBJECTS)

doc:
	doxygen Doxyfile

clean:
	rm -rf *.o *.so *~
	rm -rf doc
