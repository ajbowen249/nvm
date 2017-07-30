cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
add_definitions(
    -std=gnu++11
    -fexceptions
    -frtti
)

project(nvm VERSION 0.1 LANGUAGES CXX)

enable_testing()

add_subdirectory(googletest)
add_subdirectory(nvmCore)
add_subdirectory(nvmCore_test)
add_subdirectory(inMemoryInterface)
add_subdirectory(sandbox)
