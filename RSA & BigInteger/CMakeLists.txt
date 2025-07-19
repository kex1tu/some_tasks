cmake_minimum_required(VERSION 3.14)
project(decode)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic-errors -gdwarf-4  -std=c++20")

set(SOURCES biginteger.cpp)

add_executable(decode decode.cpp ${SOURCES})

add_executable(biginttest biginteger.cpp tests.cc)
target_link_libraries(biginttest gtest gtest_main pthread)

add_custom_target(test ALL
    COMMENT "Testing biginteger..."
    DEPENDS biginttest
    COMMAND biginttest
   
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
