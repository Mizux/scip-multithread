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
add_executable(Foo "")
target_sources(Foo
  PRIVATE
    src/main.cpp)
target_compile_features(Foo PUBLIC cxx_std_11)
set_target_properties(Foo PROPERTIES
  VERSION ${PROJECT_VERSION})
# note: macOS is APPLE and also UNIX !
if(APPLE)
  set_target_properties(Foo PROPERTIES
    INSTALL_RPATH "@loader_path/../${CMAKE_INSTALL_LIBDIR}")
elseif(UNIX AND NOT APPLE)
  set_target_properties(Foo PROPERTIES
    INSTALL_RPATH "$ORIGIN/../${CMAKE_INSTALL_LIBDIR}")
endif()

target_link_libraries(Foo PUBLIC scip::scip)
add_executable(${PROJECT_NAME}::Foo ALIAS Foo)

if(BUILD_TESTING)
  add_test(NAME Foo_test COMMAND Foo)
endif()

# Install
include(GNUInstallDirs)
install(TARGETS Foo
  EXPORT ${PROJECT_NAME}Targets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )
