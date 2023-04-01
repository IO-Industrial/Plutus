# Payroll - Payroll calculations library
# Copyright (C) 2020 Joe Turner; All rights reserved.
#
enable_testing()

set(BINARY ${CMAKE_PROJECT_NAME}_tst)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

set(SOURCES ${TEST_SOURCES})

add_executable(${BINARY} ${TEST_SOURCES})
target_link_libraries(${BINARY} PUBLIC gtest)

add_test(${BINARY} ${BINARY})

