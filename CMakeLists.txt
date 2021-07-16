cmake_minimum_required(VERSION 3.19)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 14)

add_executable(GameOfLife main.cpp src/Game.cpp include/Game.h src/Grid.cpp include/Grid.h src/Cell.cpp include/Cell.h include/Random.h)