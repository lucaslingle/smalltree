cmake_minimum_required(VERSION 3.14)
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

option(SMALLTREE_BUILD_TESTS "Build GoogleTest unit tests" ON)

if(SMALLTREE_BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1  # last release supporting C++11
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()

    add_executable(smalltree_tests
        tests/state_test.cpp
        tests/tree_test.cpp
        src/state.cpp
        src/tree.cpp
    )
    target_include_directories(smalltree_tests PRIVATE src)
    target_link_libraries(smalltree_tests PRIVATE gtest_main)

    include(GoogleTest)
    gtest_discover_tests(smalltree_tests)
endif()
