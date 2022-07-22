# A demo for OpenGL and freeglut on Ubuntu

## Required
    sudo apt install libgl1-mesa-dev libglu1-mesa-dev freeglut3-dev

## Build
    c++ src/main.cpp -o demo -lGL -lGLU -lglut

## Check OpenGL version
    glxinfo | grep "OpenGL version"
    