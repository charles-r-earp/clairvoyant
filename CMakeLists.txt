cmake_minimum_required (VERSION 2.6)
project(clairvoyant)

if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_CXX_FLAGS "--std=gnu++11 ${CMAKE_CXX_FLAGS}")
    endif ()
  else ()
    set (CMAKE_CXX_STANDARD 11)
endif ()

find_package(lambda CONFIG REQUIRED COMPONENTS lambda)
include_directories(include ${lambda_INCLUDE_DIRS})

add_subdirectory(tests)
#add_subdirectory(examples)
