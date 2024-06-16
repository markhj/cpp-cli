@page helpers Helpers

An important part of a CLI application's usability is to instruct
the user on what to do, when they don't already know the commands
and options in advance.

One way to make it easier, is to display an appropriate list of
commands and options, either upon request, or when they make a mistake.

For this purpose, C++ CLI uses "helpers". There's a default helper that
works "out of the box", and if you're satisfied with how it works, you
can theoretically already leave this article.

If you want to replace it, that's possible too.

## 📜 Contract

When writing a new helper, it has to implement the  @ref CppCLI::Helper contract.

You can review the contract from the link and/or review
the existing implementation, called @ref CppCLI::StdHelper.

## 🚀 Usage

To replace the existing helper, simply call @ref CppCLI::CLI::setHelper method.
