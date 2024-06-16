@page first-app Your first app

Great! Now it's time to start coding your CLI app ☺️

## 📚 Include

When the library is compiled and properly linked with your own, you start
off by including the public header file.

````cpp
#include "cpp-cli/cpp-cli.hpp"
````

## 👋 Hello world!

The simplest app you can write with C++ CLI, is an app
that just says "Hello, world!".

First, you'll get the full code. Afterward, we'll
go through what happened step by step.

````cpp
#include "cpp-cli/cpp-cli.hpp"

using CppCLI::CLI,
    CppCLI::ConsoleIO,
    CppCLI::Interpretation,
    CppCLI::IO,
    CppCLI::Subcommand;

int main(int argc, char *argv[]) {
    std::shared_ptr<IO> io = std::make_shared<IO>(IO());
    CLI cli("Hello World", "v1.0.0", io);

    Subcommand subcommand = Subcommand();
    subcommand.handle([](ConsoleIO &io, const Interpretation &interpretation) {
        io.emit("Hello, world!");
        return Response();
    });

    cli.define(subcommand);

    cli.run(argc, argv);

    return 0;
}

````

All right, let's break down what's happening here.

@note This example is also found in ``samples/src/hello-world.cpp``.
The file contains detailed comments.

For starters, it's important to note that this app does not take
any subcommands, options or arguments. It simply prints "Hello, world".

- First, we initialize an instance of ``IO``. In most cases, you don't need
  to worry too much about this step. ``IO`` is a class which writes information to the console.
- Then we initialize an instance of ``CLI``. ``CLI`` is the main service
  for putting everything together, from start to finish.
- Then we define a ``Subcommand``. You can have multiple of these per app.
- We proceed to specify a ``handle`` for the subcommand. When ``CLI`` has analyzed which
  subcommand to execute, this is the function that's executed
- Second last step is calling ``CLI::define`` to "add the subcommand" to its universe.
- And lastly, we run the app.

And that's it!

The next step would be to add more subcommands, and to add options to each of them.
