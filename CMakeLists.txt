cmake_minimum_required(VERSION 3.13)

project(plutus
    VERSION     1.0
    DESCRIPTION "kconfig test project"
    LANGUAGES   CXX
)

# CMAKE_MODULE_PATH is a CMAKE variable. It contains a list of paths 
# which could be used to search CMAKE modules by "include()" or "find_package()", but the default value is empty.
# Add cmake dir to search list
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

get_filename_component(NATIVE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE)
message( "NATIVE_ROOT = ${NATIVE_ROOT}")

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/plutuslib/include 
)

include(cmake/top.cmake)

if(CONFIG_TEST_OPTION)

    message("Config test_option enabled")

endif()


#
# google test
#
message("Building google test..")
add_subdirectory(third-party/googletest)

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/include 
    ${CMAKE_CURRENT_LIST_DIR}/third-party/googletest/googletest/include
    )

# unit tests
add_subdirectory(plutuslib)
add_subdirectory(unittest)
add_subdirectory(util)

