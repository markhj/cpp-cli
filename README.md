![](https://res.cloudinary.com/drfztvfdh/image/upload/v1718448651/Github/cpp-cli_jzz8id.jpg)

![GitHub Tag](https://img.shields.io/github/v/tag/markhj/cpp-cli?label=version)
![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?label=license)

**C++ CLI** (``cpp-cli``) is a library inspired by Rust's _Clap_, which 
simplifies coding CLI apps, by leveraging the bulk of the command/option/argument
parsing workload to the library.

That's at the heat of what C++ CLI does: Helps you define the structure of your CLI, and
deals with all the meticulous parsing, interpretation, error handling, and so forth.

## 🔨 Getting started

Link to GitHub Pages.

## 🚧 To-do

Believe or not, this library isn't done. Here are features planned for future releases:

- Make it easier to get started (no need to build the artifacts yourself)
  - CI/CD pipeline: Make it possible to download artifacts, instead of building them,
    as not every developer is comfortable with this approach
- Create a new class that can read the C++-provided argument list (``argc``, ``argv``) and parse
  it to a more readable format, which is easier to use in both interpretation and tests.
- Integer and float values in options/args
- ``ConsoleIO`` should be able to take input from the user
- Colored text in the console output
- Decrease requirement from C++20 to C++17
- Ability to choose standards, .e.g. if you want to allow options on the form ``-d=value``.
- Support for arguments (e.g. ``project create name`` instead of ``project create --name=name``)
    - Support positioned arguments, for example ``--a value``, which will be interpreted like `--a=value`