cmake_minimum_required(VERSION 3.16.0)
project(Pascal_Interpreter)

include(CTest)
enable_testing()

set(SOURCES
    src/main.c
    src/tokenizer.c
    src/parser.c
)

add_executable(Pascal_Interpreter ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_include_directories(Pascal_Interpreter
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)       