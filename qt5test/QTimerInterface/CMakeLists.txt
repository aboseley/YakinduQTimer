
cmake_minimum_required( VERSION 3.2 )

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE On)

add_library(QTimerInterface 
    QTimerInterface.cpp
)

target_link_libraries(QTimerInterface sc_gen Qt5::Core)
