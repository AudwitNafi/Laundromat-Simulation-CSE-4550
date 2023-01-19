cmake_minimum_required(VERSION 3.24)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled main.cpp Server.cpp Server.h Event.cpp Event.h Scheduler.cpp Scheduler.h ArrivalEvent.cpp ArrivalEvent.h Laundry.cpp Laundry.h Washer.cpp Washer.h Dryer.cpp Dryer.h Customer.cpp Customer.h DepartureEvent.cpp DepartureEvent.h)
