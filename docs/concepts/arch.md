@page arch The architecture

On this page, you'll receive a quick introduction to the architecture of the library.

At the center of the stage is the ``CLI`` class. It takes the
``argc`` and ``argv`` arguments, provided to C++'s ``main`` function. From here, it
handles everything, up to and including executing handles to each subcommand.

## 🔭 Interpretation

The first point on the agenda is **interpretation**. This is the stage where the (somewhat)
raw arguments provided by the end-user, are categorized as either subcommand,
argument or option.

Furthermore, it will catalog the findings (for example into the ``Option`` class).
The ``Interpreter`` only interprets the meaning of the arguments. It won't do any validation,
nor mapping towards your definitions. That's not its purpose.

## 🔀 Mapping

Next up is mapping the interpretation the definitions you've made in your ``CLI``.
Namely, which subcommands you have defined, and which options they each expect.

At this stage, validation is also carried out. For instance:

- If the subcommand exists
- If the option(s) exist
- If the data type provided by the end-user matches your expectations

If a problem is detected, the ``CLI`` routes through the error handling process,
otherwise through the regular handling.

## 🚀 Handling

The last stage is handling. Each ``Subcommand`` is equipped with a handler.
When interpretation and validation are successful, the mapped interpretation is passed
on the handler.

Handles are functions defined by you. Commonly as lambdas, but not required.
