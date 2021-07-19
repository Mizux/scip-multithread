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
