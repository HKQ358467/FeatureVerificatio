cmake_minimum_required(VERSION 3.26)
project(StrategyVerificatio2)

set(CMAKE_CXX_STANDARD 23)

add_executable(StrategyVerificatio2 main.cpp
        MathOperation.h
        AdditionOperation.h
        SubtractionOperation.h
        MultiplicationOperation.h
        DivisionOperation.h
        Calculator.h)
