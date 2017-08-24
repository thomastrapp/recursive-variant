cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(Value VERSION 0.1 LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

include(EnableWarnings)
include(GNUInstallDirs)

find_package(Boost REQUIRED)
find_package(Cereal REQUIRED)

add_library(Value INTERFACE)
target_include_directories(Value INTERFACE include)
target_include_directories(Value INTERFACE ${Boost_INCLUDE_DIRS})
target_include_directories(Value INTERFACE ${Cereal_INCLUDE_DIRS})

add_subdirectory("test")
enable_testing()
add_test(NAME catch COMMAND tests)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

