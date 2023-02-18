cmake_minimum_required (VERSION 2.8...3.13)

project (neutils VERSION "0.9.0")

configure_file(config.h.in config.h @ONLY)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

###############################################################################
## file globbing ##############################################################
###############################################################################

# these instructions search the directory tree when cmake is
# invoked and put all files that match the pattern in the variables
# `sources` and `data`
file(GLOB_RECURSE sources      src/main/*.cpp src/main/*.h)
file(GLOB_RECURSE data         resources/*)
file(GLOB_RECURSE sources_test src/test/*.cpp src/test/*.h)
file(GLOB_RECURSE data_test    src/test/resources/*)
file(GLOB_RECURSE sources_include  src/main/*.h)
file(GLOB_RECURSE include      include/*)
# you can use set(sources src/main.cpp) etc if you don't want to
# use globing to find files automatically

###############################################################################
## target definitions #########################################################
###############################################################################
#add_executable(NeUtils.exe ${sources} ${data})

# just for example add some compiler flags
#target_compile_options(example PUBLIC -std=c++1y -Wall -Wfloat-conversion)

# this lets me include files relative to the root src dir with a <> pair
#target_include_directories(example PUBLIC src/main)

# this copies all header files in the src/main/ directory to
# include/ directory (for usage of linked library project)
file(COPY ${sources_include} DESTINATION include)

add_library(LibNeUtils ${sources})
target_link_libraries(LibNeUtils PRIVATE stdc++fs)

###############################################################################
## dependencies ###############################################################
###############################################################################

find_package(Catch2 3 REQUIRED)
# These tests can use the Catch2-provided main
add_executable(testLibNeUtils.exe ${sources_test} ${data_test})
target_link_libraries(testLibNeUtils.exe PRIVATE Catch2::Catch2WithMain)
target_link_libraries(testLibNeUtils.exe PRIVATE LibNeUtils)
target_link_libraries(testLibNeUtils.exe PRIVATE stdc++fs)

# These tests need their own main
#add_executable(custom-main-tests test.cpp test-main.cpp)
#target_link_libraries(custom-main-tests PRIVATE Catch2::Catch2)
