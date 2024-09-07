# Example of DX11 and Vulkan interoperation in Godot

This project is a demo of DX11 library integration in Godot engine with Vulkan backend.

It consists of two parts: 
- DX11App which is a dummy DX11 application that creates shared texture and constantly updates it with different colours
- Dx11TextureView which is Godot extension which though native Vulkan methods reads shared texture and assigns it to Sprite2D

# ATTENTION
THIS IS NOT PRODUCTION CODE! MEMORY WILL BE LEAKING AND GODOT MAY BE CRASHING!
CODE AUTHOR IS PYTHON DEVELOPER AND WRITES C++ CODE FIRST TIME IN HIS LIFE!

TESTED ONLY ON AMD 8700G WITH INTEGRATED GPU

## Prerequisites

To use this on your machine, you will need the following:
- install **[CMake](https://cmake.org/)** v3.22+
- install Vulkan SDK
- install Windows SDK
- C++ Compiler with at least **C++17** support (any recent compiler)

Clone submodules:
```
git submodule update --init --recursive
```

Run cmake to generate VS project:
```
cmake . -DCMAKE_BUILD_TYPE=Debug
```

Open GDDx11InteropDemo.sln and compile extension dll.

You can configure VS to automatically start Godot with debugger attached by changing Debugging/Command in project settings.

Open project/ with modified godot binary and you will see sprite that slowly changes color.

![alt text](.readme_data/example.gif "Demonstration of texture rendering")

