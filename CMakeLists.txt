cmake_minimum_required(VERSION 3.10)
project(Satari360 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(satari360_core
    src/core/memory_bus.cpp
    src/core/m68000.cpp
    src/core/machine.cpp
)
target_include_directories(satari360_core PUBLIC src/core)

add_executable(memory_bus_smoke tests/memory_bus_smoke.cpp)
target_link_libraries(memory_bus_smoke PRIVATE satari360_core)

add_executable(m68000_smoke tests/m68000_smoke.cpp)
target_link_libraries(m68000_smoke PRIVATE satari360_core)

add_executable(machine_smoke tests/machine_smoke.cpp)
target_link_libraries(machine_smoke PRIVATE satari360_core)

enable_testing()
add_test(NAME memory_bus_smoke COMMAND memory_bus_smoke)
add_test(NAME m68000_smoke COMMAND m68000_smoke)
add_test(NAME machine_smoke COMMAND machine_smoke)
