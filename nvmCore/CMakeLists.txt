project(libnvmCore VERSION 0.1 LANGUAGES CXX)

add_library(nvmCore
    src/NVMCore.cpp
)

target_include_directories(nvmCore
    PUBLIC inc
)
