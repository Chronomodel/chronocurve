# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.15)

# Create variables
set(SRC_DIR src)
set(PROJECT_NAME Chronocurve)

# Project name and version
project(${PROJECT_NAME} VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# configure a header file to pass the version number to the source code:
configure_file(ChronocurveConfig.h.in ChronocurveConfig.h)

# add the executable
add_executable(${PROJECT_NAME}
${SRC_DIR}/main.cpp
${SRC_DIR}/Globals.cpp
${SRC_DIR}/Application.cpp
${SRC_DIR}/Exception.cpp
${SRC_DIR}/CsvReader.cpp
${SRC_DIR}/InputPoint.cpp
${SRC_DIR}/InputFile.cpp
${SRC_DIR}/InputParams.cpp
)

# Since the configured file will be written into the binary tree, 
# we must add that directory to the list of paths to search for include files :
target_include_directories(${PROJECT_NAME} PUBLIC 
    "${PROJECT_BINARY_DIR}"
)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/ChronocurveConfig.h"
    DESTINATION include
)
