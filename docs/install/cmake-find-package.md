@page cmake-find-package Install as external dependency

You can integrate the library in a number of ways.
Many prefer to have the library headers and source files entirely
outside their project scope (repository).

On this page, we review how to install the library to an arbitrary,
external location on your machine, and detect it in your project with CMake's
``find_package``.

## Clone

Start by cloning the directory to a location on
your machine (i.e. not inside the project repo.)

````
git clone https://github.com/markhj/cpp-cli
````

## Build

@include{doc} docs/install/parts/setup-submodule.md

@include{doc} docs/install/parts/build-with-cmake.md

## Integrating

When the library is located in an arbitrary location to your machine,
you don't want to have absolute paths to directories on your machine,
because on another developer's machine it may be completely different.
It most likely is completely different.

To solve this, we resort to an environment variable.  Define one called
``CPP_CLI_DIR`` which points to where you have cloned the ``cpp-cli`` repository to.

@note Depending on CMake configuration you may, or may not, need to
add ``cmake/`` to the path.

@note ``CPP_CLI_DIR`` is specific to each instance of your project (i.e. each machine),
which means C++ CLI can freely exist in different locations between machines.

The last steps are as before: Call ``find_package``.

````cmake
find_package(cpp-cli REQUIRED)
````

And lastly, you link to your executable:

````cmake
target_link_libraries(my_app PRIVATE cpp-cli)
````

@include{doc} docs/install/parts/test-integration.md

