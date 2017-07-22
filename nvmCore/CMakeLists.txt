project(libnvmCore VERSION 0.1 LANGUAGES CXX)

add_library(nvmCore
    src/Core.cpp
    src/Options.cpp
    src/RegisterTypes.cpp
)

target_include_directories(nvmCore
    PUBLIC inc
)
