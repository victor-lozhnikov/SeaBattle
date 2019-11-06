cmake_minimum_required(VERSION 3.14)
project(SeaBattle)

set(CMAKE_CXX_STANDARD 14)

add_executable(SeaBattle main.cpp Gamer.cpp Gamer.h GameView.cpp GameView.h MultiPlayer.cpp MultiPlayer.h)