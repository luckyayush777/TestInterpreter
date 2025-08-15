cmake_minimum_required(VERSION 3.10)
project(TestInterpreter)

# Set the C++ standard for the project
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define your executable and list all its source files explicitly
add_executable(TestInterpreter
    src/main.cpp
    src/lexer.cpp
    src/parser.cpp
    src/util.cpp
    src/environment.cpp
    src/expr.cpp
    src/stmt.cpp
    src/function.cpp
)

# Apply include directory settings only to the TestInterpreter target
target_include_directories(TestInterpreter PUBLIC include)

target_compile_features(TestInterpreter PUBLIC cxx_std_17)
