cmake_minimum_required(VERSION 3.10)
project(Clipper5NtxIndex)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "/O2 /NDEBUG" CACHE STRING "Release flags" FORCE)
set(CMAKE_CXX_FLAGS_DEBUG "/Zi /Od /D_DEBUG" CACHE STRING "Debug flags" FORCE)

# Visual Studio 2022 specific settings
if(MSVC)
    add_compile_options(/W4)  # Warning level 4
    add_compile_options(/EHsc)  # Exception handling
endif()

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Source files
set(NTXINDEX_SOURCES
    src/NtxIndex.cpp
)

set(NTXINDEX_HEADERS
    include/NtxIndex.h
)

# Create library
add_library(NtxIndex ${NTXINDEX_SOURCES} ${NTXINDEX_HEADERS})

# Create example executable
add_executable(NtxIndexExample src/main.cpp)
target_link_libraries(NtxIndexExample NtxIndex)

# Set startup project for Visual Studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT NtxIndexExample)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
