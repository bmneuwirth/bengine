## bengine

This is a small voxel game engine being developed using OpenGL and SDL 2.0.

### build instructions

1. clone this repo
2. install [vcpkg](https://github.com/microsoft/vcpkg) and [CMake](https://cmake.org/download/)
3. run `cmake -S . -B build  -DCMAKE_TOOLCHAIN_FILE=<vcpkg-root>/scripts/buildsystems/vcpkg.cmake` where `<vcpkg-root>` is your vcpkg install location
4. open the Visual Studio solution in `build` and build the project