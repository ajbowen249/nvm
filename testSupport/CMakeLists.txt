project(libtestSupport VERSION 0.1 LANGUAGES CXX)

add_library(testSupport
    src/ObservableCore.cpp
)

target_include_directories(testSupport
    PUBLIC inc
)

target_link_libraries(testSupport
    nvmCore
)
