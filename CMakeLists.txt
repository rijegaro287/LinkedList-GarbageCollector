cmake_minimum_required(VERSION 3.17)
project(Tarea_1_Datos_II)

set(CMAKE_CXX_STANDARD 20)

set(wxWidgets_ROOT_DIR <${CMAKE_CURRENT_SOURCE_DIR}/libs/wxWidgets-3.1.4>)
set(wxWidgets_CONFIGURATION mswu)

find_package(wxWidgets REQUIRED COMPONENTS core)
include(${wxWidgets_USE_FILE})

add_executable(Tarea_1_Datos_II Node.cpp List.cpp Collector.cpp Classes.h GUI.cpp)

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})