cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(proj-zaliczeniowy-cpp)

add_executable(proj-zaliczeniowy-cpp main.cpp transcription.cpp sequence.cpp loader.cpp translation.cpp)

install(TARGETS proj-zaliczeniowy-cpp RUNTIME DESTINATION bin)
