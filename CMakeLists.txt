cmake_minimum_required (VERSION 3.0)
project (LiseuseFabriJoly)

add_subdirectory(external/SFML)

file(GLOB_RECURSE SRC_FILES
  SRC/*
  )

include_directories(SRC)

add_executable(cbr ${SRC_FILES})

target_link_libraries(cbr sfml-window sfml-graphics)

target_include_directories(cbr SYSTEM PUBLIC external/SFML/include)
