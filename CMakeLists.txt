cmake_minimum_required (VERSION 2.8.11)
project(IndlejredeSystemer)

add_executable(runner main.c derivative.h highpass.h lowpass.h main.h mwi.h peaks.h sensor.h squarring.h)