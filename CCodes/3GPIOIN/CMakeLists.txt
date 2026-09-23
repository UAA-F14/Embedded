cmake_minimum_required(VERSION 3.16)
project(3GPIOIN C) 

add_executable(3GPIOIN
    main.c
)

target_link_libraries(3GPIOIN
    gpiod
)

