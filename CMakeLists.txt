cmake_minimum_required(VERSION 3.10)

project(proj-zaliczeniowy-cpp)

add_executable(proj-zaliczeniowy-cpp main.cpp transcription.cpp sequence.cpp loader.cpp)

install(TARGETS proj-zaliczeniowy-cpp RUNTIME DESTINATION bin)
