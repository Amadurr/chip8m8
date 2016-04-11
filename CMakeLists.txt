cmake_minimum_required(VERSION 3.3)
project(chip8_temp)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -pedantic")

set(SOURCE_FILES main.c app.h init_.c)
add_executable(chip8_temp ${SOURCE_FILES})

if(WIN32)
    target_link_libraries(chip8_temp mingw32 SDL2main SDL2 imm32 winmm version)
else()
    target_link_libraries(chip8_temp SDL2main SDL2)
endif()
