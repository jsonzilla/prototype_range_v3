cmake_minimum_required(VERSION 3.0)

project(ranges_v3)

get_filename_component(CURRENT_SOURCE_DIR ../ ABSOLUTE)

include("${CURRENT_SOURCE_DIR}/tests/gtest.cmake")


file (GLOB_RECURSE headers "${CURRENT_SOURCE_DIR}/src/*.h")
file (GLOB_RECURSE sources "${CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(ranges_v3
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

target_include_directories(ranges_v3 PUBLIC "${CURRENT_SOURCE_DIR}/src")
target_include_directories(tests PUBLIC "${CURRENT_SOURCE_DIR}/src")

find_package (Threads) # REQUIRED for Google Test
target_link_libraries(tests gtest ${CMAKE_THREAD_LIBS_INIT})

if (MSVC)
    target_compile_options(tests PRIVATE /std:c++14)

    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Ox")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od")

    add_definitions(-DGTEST_HAS_TR1_TUPLE=0)
else()
    target_compile_options(ranges_v3 PRIVATE -std=c++14 -g -fpermissive)
    target_compile_options(tests PRIVATE -std=c++14 -g -fpermissive)
endif()




