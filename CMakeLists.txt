cmake_minimum_required(VERSION 3.16)

project(DiamondSquare VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Quick Qml)

qt_add_executable(DiamondSquare
    main.cpp
    diamondsquaregenerate.h
    diamondsquaregenerate.cpp
)
qt_add_qml_module(DiamondSquare
    URI DiamondSquare
    VERSION 1.0
    QML_FILES
        Main.qml
)

target_link_libraries(DiamondSquare
    PRIVATE
        Qt6::Core
        Qt6::Quick
        Qt6::Qml
)
