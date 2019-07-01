# clang-bcapi

Introduction
------------

clang-bcapi is a tool which generate xml scheme for [Beautiful Capi](https://github.com/PetrPPetrov/beautiful-capi).

### Using

clang-bcapi use clang and requare all sources, insludes, preprocessor definitions and dependency libraries(their includes) like when you just compiling your library with clang. Additional requared argument is:
-  namespaces list
-  path/to/out_file.xml

simple example:

> clang-bcapi "MyNamespace" "scheme.xml" sources.cpp
