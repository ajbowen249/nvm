project(libnvmParser VERSION 0.1 LANGUAGES CXX)

if (WIN32)
    set(ANTLR4CPP_JAR_LOCATION C:/Javalib/antlr-4.7-complete.jar)
else()
    set(ANTLR4CPP_JAR_LOCATION /usr/local/lib/antlr-4.7-complete.jar)
endif (WIN32)

LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(ExternalAntlr4Cpp)
include_directories(${ANTLR4CPP_INCLUDE_DIRS})
link_directories(${ANTLR4CPP_LIBS})

antlr4cpp_process_grammar(libnvmParser
    antlrGenerated
    ${CMAKE_CURRENT_SOURCE_DIR}/grammar/NVMLexerRules.g4
    ${CMAKE_CURRENT_SOURCE_DIR}/grammar/NVM.g4
)

include_directories(${antlr4cpp_include_dirs_antlrGenerated})

add_library(nvmParser
    ${antlr4cpp_src_files_antlrGenerated}
    src/Parser.cpp
)

add_dependencies(nvmParser antlr4cpp antlr4cpp_generation_antlrGenerated)

target_include_directories(nvmParser
    PUBLIC inc
)

target_link_libraries(nvmParser
    nvmCore
    antlr4-runtime
)
