project(libinMemoryInterface VERSION 0.1 LANGUAGES CXX)

add_library(inMemoryInterface
    src/InMemoryInterface.cpp
)

target_include_directories(inMemoryInterface
    PUBLIC inc
)

target_link_libraries(inMemoryInterface
    nvmCore
)
