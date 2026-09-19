cmake_minimum_required(VERSION 3.13)
project(smalltree CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-stdlib=libc++)
    add_link_options(-stdlib=libc++)
endif()

add_executable(oneplayer src/oneplayer.cpp src/tree.cpp src/state.cpp)
add_executable(twoplayer src/twoplayer.cpp src/state.cpp)
add_executable(zeroplayer src/zeroplayer.cpp src/tree.cpp src/state.cpp)
