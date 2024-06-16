@page install-submodule Install as Git submodule

One way to install **C++ CLI** in your project is as a **Git submodule**.

## 🔧 Setting up

Navigate to the root of your project repository.

From there, you run the following command:

````
git submodule add https://github.com/markhj/cpp-cli <destination>
````

Replace ``<destination>`` with the path to, and name of, the directory
which should contain the submodule.

@note It's recommended to group submodules in a relevant directory, such as 
``vendor`` or ``thirdparty``. Furthermore, it's recommended to include the library name.
For instance: ``thirdparty/cpp-cli``

## Build

@include{doc} docs/install/parts/setup-submodule.md

@include{doc} docs/install/parts/build-with-cmake.md

## Connecting with your project

In your project's ``CMakeLists.txt`` file, you start by defining the path
to the library. It could look something like this:

````cmake
get_filename_component(cpp-cli_DIR "${CMAKE_CURRENT_LIST_DIR}/vendor/cpp-cli/cmake" ABSOLUTE)
````

@note Depending on how your CMake operates, you may need to remove ``cmake/`` from this path.

Next, you call ``find_package``.

````cmake
find_package(cpp-cli REQUIRED)
````

And lastly, you link to your executable:

````cmake
target_link_libraries(my_app PRIVATE cpp-cli)
````

@include{doc} docs/install/parts/test-integration.md