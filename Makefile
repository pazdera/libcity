COMPILER=g++
COMPILER_FLAGS=-Wall -fPIC -pedantic -g

ARCHIVER=ar
ARCHIVER_FLAGS=rcs

LINKER=ld

NAME=libcity
MAJOR_VERSION=0
MINOR_VERSION=1
RELEASE=1

LINKER_NAME=$(NAME).so
SONAME=$(LINKER_NAME).$(MAJOR_VERSION)
REAL_NAME=$(SONAME).$(MINOR_VERSION).$(RELEASE)

STATIC_NAME=$(NAME).a

DESTDIR=
HEADERS_INSTALL_PATH=$(DESTDIR)/usr/local/include
LIB_INSTALL_PATH=$(DESTDIR)/usr/local/lib

HEADERS_DIR=include/
DOCUMENTATION_DIR=doc/


TESTS_EXECUTABLE=unit_tests

UNITTESTCPP_LIB=../UnitTest++/libUnitTest++.a
UNITTESTCPP_INCLUDE_DIR=../UnitTest++/src/

.PHONY: install uninstall static dynamic clean doc headers test

all: static dynamic headers

# LIB Object files and sources ##########################

# Geometry package
GEOMETRY_PACKAGE=src/geometry/line.o \
                 src/geometry/linesegment.o \
                 src/geometry/point.o \
                 src/geometry/vector.o \
                 src/geometry/polygon.o \
                 src/geometry/ray.o \
                 src/geometry/shape.o

# Streetgraph package
STREETGRAPH_PACKAGE=src/streetgraph/intersection.o \
                    src/streetgraph/road.o \
                    src/streetgraph/streetgraph.o \
                    src/streetgraph/path.o \
                    src/streetgraph/rasterroadpattern.o \
                    src/streetgraph/organicroadpattern.o \
                    src/streetgraph/areaextractor.o

# LSystem package
LSYSTEM_PACKAGE=src/lsystem/lsystem.o \
                src/lsystem/graphiclsystem.o \
                src/lsystem/roadlsystem.o

# Regions package
REGIONS_PACKAGE=src/area/block.o \
                src/area/area.o \
                src/area/zone.o \
                src/area/lot.o \
                src/area/subregion.o

# Entities package
ENTITIES_PACKAGE=src/entities/urbanentity.o \
                 src/entities/building.o

# No package
MISC=src/random.o \
     src/city.o

LIB_OBJECTS=$(GEOMETRY_PACKAGE) $(STREETGRAPH_PACKAGE) $(LSYSTEM_PACKAGE) $(REGIONS_PACKAGE) $(ENTITIES_PACKAGE) $(MISC)

$(LIB_OBJECTS): %.o: %.cpp %.h
	$(COMPILER) $(COMPILER_FLAGS) -c $< -o $@



# TEST Object files and sources ##########################

# Unit tests
TEST_UNITS=test/testPoint.o   \
           test/testVector.o  \
           test/testPolygon.o \
           test/testLSystem.o \
           test/testGraphicLSystem.o \
           test/testStreetGraph.o \
           test/testLine.o \
           test/testLineSegment.o \
           test/testRasterRoadPattern.o \
           test/testRandom.o \
           test/testAreaExtractor.o \
           test/testPath.o \
           test/testRay.o \
           test/testBlock.o \
           test/testLot.o \
           test/testZone.o \
           test/testSubRegion.o \
           test/testShape.o

TEST_MAIN=test/main.o
TEST_OBJECTS=$(TEST_UNITS) $(TEST_MAIN)

$(TEST_OBJECTS): %.o: %.cpp
	$(COMPILER) $(COMPILER_FLAGS) -I$(UNITTESTCPP_INCLUDE_DIR) -c $< -o $@

static: $(LIB_OBJECTS)
	$(ARCHIVER) $(ARCHIVER_FLAGS) $(STATIC_NAME) $(LIB_OBJECTS)

dynamic: $(LIB_OBJECTS)
	$(LINKER) -shared -soname $(SONAME) -o $(REAL_NAME)  $(LIB_OBJECTS)


headers:
	mkdir -p $(HEADERS_DIR)
	cd src/ && find . -name "*.h" -exec rsync -R {} ../$(HEADERS_DIR) \; >/dev/null

install: dynamic headers
	install -p -d $(HEADERS_INSTALL_PATH)/libcity/
	cp -rp include/* $(HEADERS_INSTALL_PATH)/libcity
	install -p libcity.h -D $(HEADERS_INSTALL_PATH)/libcity.h
	install -m644 -p -s $(REAL_NAME) -D $(LIB_INSTALL_PATH)/$(REAL_NAME)
	ln -sf $(REAL_NAME) $(LIB_INSTALL_PATH)/$(LINKER_NAME)
	ln -sf $(REAL_NAME) $(LIB_INSTALL_PATH)/$(SONAME)

uninstall:
	rm -rf $(HEADERS_INSTALL_PATH)/libcity
	rm -f $(HEADERS_INSTALL_PATH)/libcity.h
	rm -f $(LIB_INSTALL_PATH)/$(REAL_NAME)
	rm -f $(LIB_INSTALL_PATH)/$(LINKER_NAME)
	rm -f $(LIB_INSTALL_PATH)/$(SONAME)

test: $(TEST_OBJECTS) static
	$(COMPILER) $(COMPILER_FLAGS) -I$(UNITTESTCPP_INCLUDE_DIR) -o $(TESTS_EXECUTABLE) $(TEST_OBJECTS) $(UNITTESTCPP_LIB) libcity.a

doc:
	rm -rf doc/
	doxygen Doxyfile

clean:
	rm -rf *.o *.so* *.a *~
	rm -rf $(DOCUMENTATION_DIR)
	rm -rf $(HEADERS_DIR)
	rm -f $(LIB_OBJECTS)
	rm -f $(TEST_OBJECTS)
