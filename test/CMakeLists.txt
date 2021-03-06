include(ExternalProject)
find_package(Git REQUIRED)

ExternalProject_Add(
  catch
  PREFIX ${CMAKE_BINARY_DIR}/catch
  GIT_REPOSITORY https://github.com/philsquared/Catch.git
  TIMEOUT 10
  UPDATE_COMMAND ${GIT_EXECUTABLE} pull
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  LOG_DOWNLOAD ON
)

# Expose required variable (CATCH_INCLUDE_DIR) to parent scope
ExternalProject_Get_Property(catch source_dir)
set(CATCH_INCLUDE_DIR ${source_dir}/single_include CACHE INTERNAL "Path to include folder for Catch")

add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

add_executable(tests ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
add_dependencies(tests catch)
set_target_properties(tests PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED On)
target_link_libraries(tests Catch Value)

