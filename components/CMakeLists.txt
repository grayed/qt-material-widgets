# cmake version
cmake_minimum_required(VERSION 3.5.0)

# project
project(qtmeterial)

# source
file(GLOB_RECURSE SOURCES *.cpp *.h *.qrc *.ui)

# qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

# target
include_directories(../components)
add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets)

# tips
foreach(SOURCE ${SOURCES})
  message(STATUS "build with: " ${SOURCE})
endforeach(SOURCE)
