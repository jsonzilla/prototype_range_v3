cmake_minimum_required(VERSION 3.0)

project(template-simple-gtest)

get_filename_component(CURRENT_SOURCE_DIR ../ ABSOLUTE)

include("${CURRENT_SOURCE_DIR}/tests/gtest.cmake")


file (GLOB_RECURSE headers "${CURRENT_SOURCE_DIR}/src/*.h")
file (GLOB_RECURSE sources "${CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(template-simple-gtest
    ${headers}
    ${sources}
    )

file (GLOB_RECURSE headersTests "${CURRENT_SOURCE_DIR}/tests/*.h")
file (GLOB_RECURSE sourcesTests "${CURRENT_SOURCE_DIR}/tests/*.cpp")

list(FILTER sources EXCLUDE REGEX ".*\\main.cpp$")

add_executable(tests
    ${headers}
    ${sources}
    ${headersTests}
    ${sourcesTests}
    )

target_include_directories(template-simple-gtest PUBLIC "${CURRENT_SOURCE_DIR}/src")
target_include_directories(tests PUBLIC "${CURRENT_SOURCE_DIR}/src")

find_package (Threads) # REQUIRED for Google Test
target_link_libraries(tests gtest ${CMAKE_THREAD_LIBS_INIT})

if (MSVC)
    target_compile_options(tests PRIVATE /std:c++17)

    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Ox")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od")

    add_definitions(-DGTEST_HAS_TR1_TUPLE=0)
else()
    target_compile_options(template-simple-gtest PRIVATE -std=c++17 -g -fpermissive)
    target_compile_options(tests PRIVATE -std=c++17 -g -fpermissive)
endif()




