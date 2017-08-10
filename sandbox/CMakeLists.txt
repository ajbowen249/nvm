add_executable(sandbox
    src/main.cpp
)

target_include_directories(sandbox
    PUBLIC inc
)

target_link_libraries(sandbox
    inMemoryInterface
    testSupport
)
