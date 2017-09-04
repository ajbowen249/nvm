add_executable(parserDriver
    src/main.cpp
)

target_include_directories(parserDriver
    PUBLIC inc
)

target_link_libraries(parserDriver
    nvmParser
)
