[![Build Status](https://travis-ci.org/alexa/webvtt.svg?branch=master)](https://travis-ci.org/alexa/webvtt)

# libwebvtt
A C/C++ library for interpreting and authoring conformant [WebVTT](https://www.w3.org/TR/webvtt1/) content. WebVTT is a
caption and subtitle format designed for use with HTML5 audio and video elements. This project is a fork of 
[caitp/webvtt](https://github.com/caitp/webvtt).

## Build Instructions:

[CMake](https://cmake.org/) is used for running the builds and tests. When using CMake, it's recommended that builds 
take place outside of the main project source, such as in a `build` directory.


### Building and Running the `parsevtt` Sample Program

```bash
# assuming the current working directory is the project directory
cd build

# configure the project with CMake
cmake ..

# compile the test executable
make

# Run the sample executable with a WebVTT file as input,
# using the -f argument to point to the file location.
src/parsevtt/parsevtt -f ../test/webvtt_example.vtt
```

Once built, the static library and include files are available at these locations:

#### For C
* Static library: `build/src/webvtt/libwebvtt.a`
* Include: `include/webvtt`

#### For C++
* Static library: `build/src/webvttxx/libwebvttxx.a`
* Include: `include/webvttxx`

### Building a .dll in Windows (MinGW)
[CMake](https://cmake.org/) is also used on Windows for running the builds and tests, but it's recommended to use [MSYS2](https://www.msys2.org/) to create the Mingw64 build environment.

When using CMake, it's recommended that builds take place outside of the main project source, such as in a `build` directory.

1. [Download, install, and update MSYS2 using the steps on the MSYS2 homepage](https://www.msys2.org/)
2. Open the MSYS2 terminal, choosing "Mingw-w64 64 bit" when prompted
3. Change directories to the working folder where you want to build libwebvtt. Keep in mind that the C:\ for Windows is mounted under `/c/` in MinGW. For example, if the build location is "C:\Users\username\sources\", then do `cd /c/users/username/sources/`

```bash
# clone the project
git clone https://github.com/alexa/webvtt.git

# change directories to the project root
cd webvtt

# create and enter the build directory
mkdir build && cd build

# configure the project with CMake, using the MSYS generator
cmake -G 'MSYS Makefiles' -DBUILD_LIBRARY=1 ..

# compile the DLL
make libwebvtt
```

### Building in Microsoft Visual Studio 10 with UWP
1. Download or clone this repository.
2. Ensure that [Visual Studio Installer](https://docs.microsoft.com/en-us/visualstudio/install/install-visual-studio?view=vs-2019) has installed the following Workloads:
  * Desktop development with C++
  * Universal Windows Platform development
3. Open Microsoft Visual Studio, and File -> Open -> CMake...
4. Navigate to this project's CMakeLists.txt in the root project directory. This will import the Webvtt project. This project's Visual Studio settings are in CMakeSettings.json. It's configured already to build libwebvtt.dll.
5. Select Build -> Build All. This will produce a .lib and a .dll file in out/build/x64-Debug/src/webvtt, and some .lib files in the other src/ directories.

## Running Tests:

All tests are written using [Google Test](https://github.com/google/googletest).

```bash
# assuming the current working directory is the project directory
cd build

# configure the project with CMake
cmake ..

# compile the test executable
make all test

# run the test executable
test/unit/unittests
```

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/alexa/webvtt/tags). 


## License

This project is licensed under the 2-Clause BSD License - see the [LICENSE](LICENSE) file for details.


## Acknowledgments

This project was originally the work of these individuals: Ralph Giles, Caitlin Potter, Rick Eyre, Edwin Lim, Dale Karp, 
Michael Afidchao, Shayan Ahmad, Jordan Raffoul, David Humphrey, Vince Lee, Mandeep Garg, Anh Tran, 
Thevakaran Virutthasalam, Mike Shutov, Michael Stiver-Balla, Kyle Barnhart, and David Perit. Many thanks to these people
for their efforts!
