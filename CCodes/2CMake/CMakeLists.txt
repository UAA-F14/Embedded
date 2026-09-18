cmake_minimum_required(VERSION 3.16)
project(2CMake C) 

add_executable(2CMake
    main.c
)

target_link_libraries(2CMake
    gpiod
)

