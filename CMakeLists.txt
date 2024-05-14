cmake_minimum_required(VERSION 3.27)
project(extra2)

set(CMAKE_CXX_STANDARD 17)

add_executable(extra2 main.cpp
        size.cpp
        size.h
        point.cpp
        point.h
        rectangle.cpp
        rectangle.h
        image.cpp
        image.h
        ImageProcessing.cpp
        ImageProcessing.h
        drawing.cpp
        drawing.h)
