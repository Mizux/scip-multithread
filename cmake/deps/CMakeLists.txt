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
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(BUILD_TESTING OFF)

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

# ZLIB
message(CHECK_START "Fetching ZLIB")
list(APPEND CMAKE_MESSAGE_INDENT "  ")
FetchContent_Declare(
  zlib
  GIT_REPOSITORY "https://github.com/madler/ZLIB.git"
  GIT_TAG "v1.2.11"
  PATCH_COMMAND git apply "${CMAKE_CURRENT_LIST_DIR}/ZLIB.patch")
FetchContent_MakeAvailable(zlib)
list(POP_BACK CMAKE_MESSAGE_INDENT)
message(CHECK_PASS "fetched")

# SCIP
message(CHECK_START "Fetching SCIP")
list(APPEND CMAKE_MESSAGE_INDENT "  ")
set(SHARED OFF)
set(READLINE OFF)
set(GMP OFF)
set(PAPILO OFF)
set(ZIMPL OFF)
set(IPOPT OFF)

set(TPI "tny" CACHE STRING "Scip param")
set(EXPRINT "none" CACHE STRING "Scip param")
set(LPS "none" CACHE STRING "Scip param")
set(SYM "none" CACHE STRING "Scip param")
FetchContent_Declare(
  scip
  GIT_REPOSITORY https://github.com/scipopt/scip.git
  GIT_TAG        master
  #URL "${CMAKE_CURRENT_LIST_DIR}/scip-7.0.1.tgz"
  #PATCH_COMMAND git apply --ignore-whitespace "${CMAKE_CURRENT_LIST_DIR}/scip-7.0.1.patch"
  )
FetchContent_MakeAvailable(scip)
#set(LPI_GLOP_SRC ${scip_SOURCE_DIR}/src/lpi/lpi_glop.cpp PARENT_SCOPE)
list(POP_BACK CMAKE_MESSAGE_INDENT)
message(CHECK_PASS "fetched")

