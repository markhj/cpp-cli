@page prerequisites Prerequisites

## ➕ C++

The library requires **C++20 or higher**.

@note It's on the agenda to decrease the language requirement to C++17.
Among a few other factors for choosing C++20, is usage of ``std::format``
which can be replaced by custom-built methods.

## 🔧 CMake

The build system centers around **CMake**. sYou will need CMake to make use of our guides.

@note It might be possible to build with another software, but this is not part
of our official support.

@note The library is written CMake version ``3.28``, but a downgrade is
most likely possible.
