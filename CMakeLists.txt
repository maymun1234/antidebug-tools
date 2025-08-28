cmake_minimum_required(VERSION 3.10)
project(ProfessionalSecurityTool VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# Define a macro for exporting/importing symbols
if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

# Glob all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add the library
add_library(SecurityTool SHARED ${SOURCES})

# Add the test executable
add_executable(TestRunner tests/test.cpp)

# Link the test executable to the library
target_link_libraries(TestRunner PRIVATE SecurityTool)
