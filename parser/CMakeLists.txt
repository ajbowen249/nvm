project(libnvmParser VERSION 0.1 LANGUAGES CXX)

if (WIN32)
    set(ANTLR4CPP_JAR_LOCATION C:/Javalib/antlr-4.7-complete.jar)
else()
    set(ANTLR4CPP_JAR_LOCATION /usr/local/lib/antlr-4.7-complete.jar)
endif (WIN32)

LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(ExternalAntlr4Cpp)

antlr4cpp_process_grammar(libnvmParser
    antlrGenerated
    ${CMAKE_CURRENT_SOURCE_DIR}/grammar/NVMLexerRules.g4
    ${CMAKE_CURRENT_SOURCE_DIR}/grammar/NVM.g4
)

add_library(nvmParser
    ${antlr4cpp_src_files_antlrGenerated}
    src/Parser.cpp
)

if (WIN32)
    add_dependencies(nvmParser antlr4cpp_generation_antlrGenerated)
    set(ANTLR4_CPP_RUNTIME C:/lib/antlr4-cpp-runtime-4.7)

    target_include_directories(nvmParser
        PUBLIC inc
        PRIVATE ${antlr4cpp_include_dirs_antlrGenerated}
        PRIVATE ${ANTLR4_CPP_RUNTIME}/antlr4-runtime
    )

    set(LINK_PATH "${ANTLR4_CPP_RUNTIME}/lib/vs-2015")

    if(${CMAKE_SYSTEM_PROCESSOR} MATCHES ".*64")
        set(LINK_PATH "${LINK_PATH}/x64")
    else()
        set(LINK_PATH "${LINK_PATH}/x86")
    endif()

    target_link_libraries(nvmParser
        nvmCore
        ${LINK_PATH}/Release DLL/antlr4-runtime.lib
    )
else()
    include_directories(${ANTLR4CPP_INCLUDE_DIRS})
    include_directories(${antlr4cpp_include_dirs_antlrGenerated})
    link_directories(${ANTLR4CPP_LIBS})

    add_dependencies(nvmParser antlr4cpp antlr4cpp_generation_antlrGenerated)

    target_include_directories(nvmParser
        PUBLIC inc
    )

    target_link_libraries(nvmParser
        nvmCore
        ${ANTLR4CPP_LIBS}/libantlr4-runtime.a
    )
endif (WIN32)
