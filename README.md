Planets
=======

Planet calculations

## usage

The simualtion only uses the hardcoded solar system

TODO : Use user defined solar systems with the save file system


- On windows, the output file is saved in the current directory.
- On linux, the output file is saved in the /tmp directory

## Instalation

### UNIX / WSL

cmake version 3.x.x required
clang or g++

```
cmake -S . -B build
cmake --build build
```

### WINDOWS with visual studio 2022

Open a cmake project and select the top CMakeLists.txt

tinker with the build system
