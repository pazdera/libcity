FILE(GLOB_RECURSE src "*.cpp" "*.h")
ADD_LIBRARY(libcity ${src})
INSTALL(TARGETS libcity DESTINATION lib)