@page tutorial-subcommands Adding subcommands

You can add multiple subcommands, simply by calling the @ref CppCLI::CLI::define
as many times, as you like.

````cpp
cli.define(Subcommand("project", "Manage projects."));
cli.define(Subcommand("config", "View and change the configuration."));
cli.define(Subcommand("about", "See version and contributors."));
````

## ⤵️ Nested subcommands

In more complex CLI apps, you may have to nest subcommands
under other subcommands.

To learn how to do that, read here: @ref subcommand-structure
