---
tags:
  - c
  - compile
Owner: Victor Jamet Soler
Status: in progress
---


Each CMake C/C++ Project requires a CMakeLists.txt file inside the Project Folder

	-- CMakeLists.txt

```cmake

cmake_minimum_required (VERSION 3.8)

# Habilite Recarga activa para los compiladores de MSVC si se admiten.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("API-Integration")

# Agregue un origen al ejecutable de este proyecto.
add_executable (API-Integration "API-Integration.cpp" "API-Integration.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET API-Integration PROPERTY CXX_STANDARD 20)
endif()

# TODO: Agregue pruebas y destinos de instalación si es necesario.

```
## C++ flags

| Flags     | Definition                      |
| --------- | ------------------------------- |
| **`-O#`** | Control optimization settings   |
| **`-O0`** | Optimization for debug builds   |
| **`-O2`** | Optimization for release builds |
| **`-O3`** | Adds aditional optimization     |


| OS      |   Build  |     |
| ------- | --- | --- |
| Windows |     |     |
| Linux   |     |     |
