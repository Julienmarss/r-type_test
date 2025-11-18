cmake_minimum_required(VERSION 3.20)
project(RType VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra)
endif()

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
)
set(BUILD_SHARED_LIBS OFF)
FetchContent_MakeAvailable(SFML)

add_subdirectory(engine)
add_subdirectory(game)
add_subdirectory(server)