@page install-in-repo Install as part of repository

@warning This is not a recommended approach. But if you understand what it entails, and
feel it matches your choices, then here's how to proceed.

What we will briefly discuss here, is how to simply include the library as an actual
part of your repository/project scope.

## ⬇️ Cloning

Create a directory in your repo to contain third-party libraries,
if you don't already have. Common names would ``thirdparty`` or ``vendor``.

Download the files from
[C++ CLI GitHub repository](https://github.com/markhj/cpp-cli),
and copy them to your repository, but leave out the ``.git`` directory.

The ``cpp-cli`` is now part of your project repository.

## Build

@include{doc} docs/install/parts/setup-submodule.md

@include{doc} docs/install/parts/build-with-cmake.md

@warning Unless explicitly excluded, remember that the entire
library source code (and compiled artifacts) will get committed
to your repository.

## Integrating

Depending on where you added the library within your repository,
you can either directly include it, or specify the include directory
via ``CMakeLists.txt``.
