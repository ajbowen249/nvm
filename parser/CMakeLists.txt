project(libnvmParser VERSION 0.1 LANGUAGES CXX)

add_library(nvmParser
)

target_include_directories(nvmParser
    PUBLIC inc
)

target_link_libraries(nvmParser
    nvmCore
)
