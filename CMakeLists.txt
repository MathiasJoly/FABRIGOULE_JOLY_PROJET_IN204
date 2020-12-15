cmake_minimum_required (VERSION 3.0)
project (Whatever)

# CONFIG COMPILATION
if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

file(GLOB_RECURSE WHATEVER_FILES
  include/whatever/*
  src/*
  )

include_directories(include)
add_executable(whatever ${WHATEVER_FILES})