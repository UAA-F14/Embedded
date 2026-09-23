cmake_minimum_required(VERSION 3.16)
project(4LIBRARY C) 

add_executable(4LIBRARY
    src/gpio.c
    src/main.c
)
target_include_directories(4LIBRARY
    PRIVATE
    include
)
target_link_libraries(4LIBRARY
    gpiod
)

