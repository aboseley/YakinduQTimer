
cmake_minimum_required( VERSION 3.2 )
project(qt5test)

find_package(Qt5Core REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory( QTimerInterface )
add_subdirectory( sc_gen )

add_executable(qt5test 
./src/DefaultStateChartDriver.cpp
./src/qt5test.cpp
)
  
target_link_libraries(qt5test sc_gen QTimerInterface Qt5::Core)
