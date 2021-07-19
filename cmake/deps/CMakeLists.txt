set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(BUILD_TESTING OFF)

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

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
  URL "${CMAKE_CURRENT_LIST_DIR}/scip-7.0.1.tgz"
  PATCH_COMMAND git apply --ignore-whitespace "${CMAKE_CURRENT_LIST_DIR}/scip-7.0.1.patch")
FetchContent_MakeAvailable(scip)
#set(LPI_GLOP_SRC ${scip_SOURCE_DIR}/src/lpi/lpi_glop.cpp PARENT_SCOPE)
list(POP_BACK CMAKE_MESSAGE_INDENT)
message(CHECK_PASS "fetched")

