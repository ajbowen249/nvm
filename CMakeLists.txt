cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

if (WIN32)
    set(CMAKE_CXX_FLAGS_RELEASE "/MT")
    set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
	option(CMAKE_USE_WIN32_THREADS_INIT "using WIN32 threads" ON)
endif (WIN32)

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
add_subdirectory(testSupport)
add_subdirectory(parser)
add_subdirectory(parserDriver)
add_subdirectory(sandbox)
