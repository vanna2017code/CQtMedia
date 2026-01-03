cmake_minimum_required(VERSION 3.16)
project(CQtMedia LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Multimedia)

add_executable(CQtMedia
    src/main.cpp
    src/MainWindow.h src/MainWindow.cpp
    src/AIEngine.h src/AIEngine.cpp
    src/ChapterBar.h src/ChapterBar.cpp
)

target_link_libraries(CQtMedia PRIVATE Qt6::Widgets Qt6::Multimedia)
