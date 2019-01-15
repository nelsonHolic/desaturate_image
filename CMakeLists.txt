cmake_minimum_required(VERSION 3.13)
project(image_processing)

set(CMAKE_CXX_STANDARD 14)

add_executable(image_processing main.cpp)

add_definitions( -DMAGICKCORE_QUANTUM_DEPTH=16 )
add_definitions( -DMAGICKCORE_HDRI_ENABLE=0 )
find_package(ImageMagick COMPONENTS Magick++ convert)
include_directories(${ImageMagick_INCLUDE_DIRS})
target_link_libraries(image_processing  ${ImageMagick_LIBRARIES})