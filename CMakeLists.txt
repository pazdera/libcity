CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(libcity)

# set cmake module path
SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

set(CMAKE_DEBUG_POSTFIX "_d")

# includes
#INCLUDE(PathHelper)
#INCLUDE(AutoLibDiscovery)
#INCLUDE(CopyInstallDLLs)

# setup CPack
#INCLUDE(InstallRequiredSystemLibraries)
SET(CPACK_PACKAGE_CONTACT "Patrick Charrier <patrick.charrier@gmail.com>")
SET(CPACK_PACKAGE_DESCRIPTION "libcity")
INCLUDE(CPack)

ADD_SUBDIRECTORY(src)

INSTALL(DIRECTORY "src/." DESTINATION "include/libcity" PATTERN "*.h")
INSTALL(FILES libcity.h DESTINATION "include")