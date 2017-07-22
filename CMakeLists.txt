cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
add_definitions(
    -std=gnu++11
    -fexceptions
    -frtti
)

project(nvm VERSION 0.1 LANGUAGES CXX)

add_subdirectory(nvmCore)
add_subdirectory(inMemoryInterface)
add_subdirectory(sandbox)
