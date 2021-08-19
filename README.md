# Alien-Landscapes-SFML

The alien landscape generator creates Brownian-motion type random landscapes. It includes a simple 3D-engine (non-moving camera, no clipping) and landscape generator together with a simple lighting-scheme.

![Screenshot from 2021-08-19 13-48-29](https://user-images.githubusercontent.com/20295285/130063579-e80636ef-267d-48e9-ad6e-953a86d74327.png)

Zoom in/out using the mouse wheel. Generate a new landscape by pressing SPACE. Left-Shift and mouse wheel will speed-up/slow-down landscape rotation.

It is the same as the JAVA version but written in C++ (ver. 14) with the SFML libraries on Linux (Ubuntu). This version is many times faster than the JAVA version and will also run on an Raspberry PI v. 4 at a triangle grid size of 100( * 100). It should run on Windows and macos as long as the SFML libraries are installed. It can be compiled with GCC/G++ as follows:

g++ -c main.cpp ThreeDEngine.cpp Lightning.cpp LandscapeEngine.cpp -O3

g++ main.o ThreeDEngine.o Lightning.o LandscapeEngine.o -o landscapes -lsfml-graphics -lsfml-window -lsfml-system -lpthread


I have also included a CMake file (CMakeLists.txt) for use with CLion.
