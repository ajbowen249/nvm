include_directories(${gtest_SOURCE_DIR}/include)

add_executable(nvmCore_test
    src/Add.cpp
)

target_link_libraries(nvmCore_test 
    gtest_main
	inMemoryInterface
	testSupport
)

add_test(nvmCore_test 
    nvmCore_test
)
