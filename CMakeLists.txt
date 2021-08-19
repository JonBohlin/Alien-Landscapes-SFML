cmake_minimum_required(VERSION 3.19)
project(AlienLandscapes)

set(CMAKE_CXX_STANDARD 14)

set(SFML_INCLUDE_DIR "/usr/include/SFML/")
set(CMAKE_CXX_FLAGS "-O3")
include_directories(SFML_INCLUDE_DIR)
find_package(SFML COMPONENTS graphics window system audio network)
add_executable(AlienLandscapes main.cpp ThreeDEngine.cpp Lightning.cpp LandscapeEngine.cpp)

target_link_libraries (AlienLandscapes sfml-graphics sfml-window sfml-system pthread)