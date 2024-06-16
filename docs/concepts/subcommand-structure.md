@page subcommand-structure Subcommand structure

In complex applications, you'll probably need to nest
subcommands under other subcommands.

To achieve this, you can use @ref CppCLI::Subcommand::addSubcommand.

## 📥 How it works

Subcommands are nested under _other_ subcommands. This makes it theoretically
possible to have "unlimited" levels.

````cpp
Subcommand top_level = Subcommand("top-level", "Top level command.");

Subcommand nested_a = Subcommand("a", "Nested command A");
Subcommand nested_b = Subcommand("b", "Nested command B");

top_level.addSubcommand(a);
top_level.addSubcommand(b);

cli.define(top_level);
````

In this example, the ``top_level`` has to two nested commands.
This means the end-user can each the two nested commands, by typing
``top-level a`` or ``top-level b``.

## 🏆 Example

You can find a working example under ``samples/src/subcommand-tree.cpp``.