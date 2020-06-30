cmake_minimum_required (VERSION 3.2)

set (MODEL_NAME Heater)

project (Heater)

add_executable(Heater
  include/fmi2Functions.h
  include/fmi2FunctionTypes.h
  include/fmi2TypesPlatform.h
  src/heater.c
  Heater/sources/all.c
)

target_include_directories(Heater PUBLIC
  include
  Heater/sources
)

if (MSVC)
  add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
  target_link_libraries(Heater shlwapi.lib)
endif ()
