@page tutorial-options Adding options

In this guide, we'll look at how you can add options
to your subcommands.

## 🌿 Basics

An option is attached to a subcommand with the ``addOption`` method.

````cpp
Subcommand subcommand = Subcommand();
subcommand.addOption({
    .id = "option-name",
    // Properties of DefineOption goes here
});
````

All properties are specified here @ref CppCLI::DefineOption.

## 🔤 Data type

If you don't specify a data type, the default will be boolean (flag).

You can expect a string with:

````cpp
.dataType = CppCLI::OptionDataType::String
````

## 🔠 Short and long name

The ``id`` is sort of an "internal ID", which you will use to read the value.
But toward the end-user, you'll need to specify at least one of ``short_name``
or ``long_name``.

You can specify both, if you wish. They will in any case get automtically
mapped to their @ref CppCLI::DefineOption.

````cpp
subcommand.addOption({
    .id = "option-name",
    // ...
    .short_name = 'n',
    .long_name = "name",
    // Properties of DefineOption goes here
});
````

@note Pay attention to that ``short_name`` is a ``char``, and must be set with
single-quotes.

## ✏️ Description

You should almost always provide a description, which will be displayed to the end-user
when they make an error or request ``--help``.

````cpp
subcommand.addOption({
    .id = "first-name",
    // ...
    .description = "Your first name",
    // ...
});
````

## 🔣 Default values

You can set default values using ``defaultValue``.

See @ref CppCLI::Value.

### Boolean
````cpp
subcommand.addOption({
    // ...
    .defaultValue = Value(false),
    // ...
});
````

### String
````cpp
subcommand.addOption({
    // ...
    .defaultValue = Value("Default value"),
    // ...
});
````

## 😠 Required values

To _require_ a value, you set ``required`` to ``true``.

````cpp
subcommand.addOption({
    // ...
    .required = true,
    // ...
});
````

If the end-user doesn't provide a value, the @ref CppCLI::CLI instance
will catch the mistake, and ask the user to correct it.

@note This happens prior to reaching @ref CppCLI::Subcommand ``handle`` method, meaning
you won't have to manually deal with requirements. You can rely on the fact
that required values are present, when the ``handle`` executes.

@warning The above is only true for options with ``required=true``.
Those without can still appear without any content.

## 📗 Reading options

Often, you'll need to read the values within your @ref Subcommand ``handle`` methods.

### Boolean
````cpp
Subcommand subcommand = Subcommand();
subcommand.handle([](ConsoleIO &io, const Interpretation &interpretation) {
    if (interpretation.hasFlag("show-help")) {
        // Do something
    }
});
````

### String
````cpp
Subcommand subcommand = Subcommand();
subcommand.handle([](ConsoleIO &io, const Interpretation &interpretation) {
    // Make sure to either check the std::optional, or set the
    // the DefineOption to required=true.
    io->emit(interpretation.getOption("name").value().value.getAsString());
});
````

@note It's recommended to check @ref CppCLI::Value closer. 
