# What is this?
Chromium Embedded Framework (CEF) implementation of the helper subprocess, used internally by the bevy-overlay crate.

## Build requirements
Compiling this repo follows roughly the same requirements that [CEF](https://github.com/chromiumembedded/cef) and [CEF-Project](https://github.com/chromiumembedded/cef-project) request. That is:
1. CMake 3.21 or later
2. Platform-specific build tools
  * Windows: Visual Studio 2022 or newer. Build automation can be achieved through MSBuild, though building manually is possible.
  * MacOS: Xcode 12.2 to 15.0 building on MacOS 10.15.4 (Catalina) or newer. The Xcode command-line tools must also be installed.

## Building

### Windows
```
# create a separate directory for the build files, and enter it
mkdir build
cd build

# run CMake for the parent folder
cmake -G "Visual Studio 17 2022" ..

# run MSBuild for the generated solution
msbuild.exe ./CEFHelperProcess.sln
```
