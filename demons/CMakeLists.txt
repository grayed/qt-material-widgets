# cmake version
cmake_minimum_required(VERSION 3.5.0)

# project
project(qtmeterial-demons)

# source
file(GLOB_RECURSE SOURCES *.cpp *.h *.qrc *.ui)

# qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)

# target
include_directories(../qtmaterial/components)
include_directories(../qtmaterial)
add_executable(${PROJECT_NAME} WIN32 ${SOURCES} demons.rc)
target_link_libraries(${PROJECT_NAME} qtmeterial)
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Gui)

# tips
foreach(SOURCE ${SOURCES})
  message(STATUS "build with: " ${SOURCE})
endforeach(SOURCE)
