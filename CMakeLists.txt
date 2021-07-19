# Copyright 2021 Google LLC
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
cmake_minimum_required(VERSION 3.18)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(MultiThread VERSION 0.1 LANGUAGES CXX)
message(STATUS "project: ${PROJECT_NAME}")
message(STATUS "version: ${PROJECT_VERSION}")

# Force default build type to RelWithDebInfo
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING
    "Choose the type of build, options are: Debug, Release (default), RelWithDebInfo and MinSizeRel."
    FORCE)
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Layout build dir like install dir
include(GNUInstallDirs)
if(UNIX)
  option(BUILD_SHARED_LIBS "Build shared libraries(.so or .dyld)." ON)
  set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
  # for multi-config build system (e.g. Xcode, ninja Multi-Config)
  foreach(OUTPUTCONFIG IN LISTS CMAKE_CONFIGURATION_TYPES)
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/${OUTPUTCONFIG}/${CMAKE_INSTALL_LIBDIR})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/${OUTPUTCONFIG}/${CMAKE_INSTALL_LIBDIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/${OUTPUTCONFIG}/${CMAKE_INSTALL_BINDIR})
  endforeach()
else()
  # Currently Only support static build for windows
  set(BUILD_SHARED_LIBS OFF)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
  # for multi-config builds (e.g. msvc)
  foreach(OUTPUTCONFIG IN LISTS CMAKE_CONFIGURATION_TYPES)
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/${OUTPUTCONFIG}/${CMAKE_INSTALL_BINDIR})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/${OUTPUTCONFIG}/${CMAKE_INSTALL_BINDIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/${OUTPUTCONFIG}/${CMAKE_INSTALL_BINDIR})
  endforeach()
endif()

# Check dependencies
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREAD_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

# Build SCIP dependency
add_subdirectory(cmake/deps deps)
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR}/deps/install)

include(CTest)
if(BUILD_TESTING)
  include(FetchContent)
  #FetchContent_Declare(
  #  googletest
  #  GIT_REPOSITORY https://github.com/google/googletest.git
  #  GIT_TAG master)
  #set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  #FetchContent_MakeAvailable(googletest)
endif()

add_subdirectory(Foo)

# Install
install(EXPORT MultiThreadTargets
  NAMESPACE MultiThread::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MultiThread
  COMPONENT Devel)
include(CMakePackageConfigHelpers)
configure_package_config_file(cmake/MultiThreadConfig.cmake.in
  "${PROJECT_BINARY_DIR}/MultiThreadConfig.cmake"
  INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/MultiThread"
  NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO)
write_basic_package_version_file(
  "${PROJECT_BINARY_DIR}/MultiThreadConfigVersion.cmake"
  COMPATIBILITY SameMajorVersion)
install(
  FILES
  "${PROJECT_BINARY_DIR}/MultiThreadConfig.cmake"
  "${PROJECT_BINARY_DIR}/MultiThreadConfigVersion.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/MultiThread"
  COMPONENT Devel)
