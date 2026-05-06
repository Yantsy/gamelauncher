cmake_minimum_required(VERSION 3.28)

project(launcher)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 COMPONENTS Widgets Core REQUIRED)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(${PROJECT_NAME}
src/main.cpp
src/mainwindow.cpp
src/mainwindow.hpp
)

qt_add_resources(${PROJECT_NAME} resources.qrc)

target_link_libraries(${PROJECT_NAME}  PUBLIC Qt6::Core Qt6::Widgets)