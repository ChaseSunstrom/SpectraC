cmake_minimum_required(VERSION 3.25.1)
project(SpectraC CXX)

set(CMAKE_CXX_STANDARD 23)

# Create a list of source files
set(SOURCES
    src/main.cpp
    src/types.hpp
    src/lang/run.cpp
    src/lang/args.hpp
    src/lexer/lexer.cpp
    src/lexer/lexer.hpp
    src/lexer/token.hpp
    src/lexer/token_type.hpp
    src/lexer/token_type.cpp
    src/lexer/keywords.hpp
    src/lexer/keywords.cpp)

# Create the executable
add_executable(SpectraC ${SOURCES})

# Add include directories
target_include_directories(SpectraC PRIVATE src)

# Add precompiled header
target_precompile_headers(SpectraC PRIVATE src/pch.hpp)
