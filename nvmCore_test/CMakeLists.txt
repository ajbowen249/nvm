include_directories(${gtest_SOURCE_DIR}/include)

add_executable(nvmCore_test
    src/BasicTestFixture.cpp
    src/Add.cpp
    src/Jump.cpp
    src/Return.cpp
    src/Increment.cpp
    src/Decrement.cpp
    src/Read.cpp
    src/Write.cpp
    src/Push.cpp
)

target_include_directories(nvmCore
    PUBLIC inc
)

target_link_libraries(nvmCore_test
    gtest_main
    inMemoryInterface
    testSupport
)

add_test(nvmCore_test
    nvmCore_test
)
