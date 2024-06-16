#pragma once

#include "cpp-cli/utilities/value.hpp"
#include "enums.hpp"
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace CppCLI {
    /**
     * Returned by the `handle` method in a Subcommand.
     */
    struct Response {
        /**
         * Indicates if the response contains information about
         * errors, or if it comes from a successful operation.
         */
        ResponseState state = ResponseState::Success;

        /**
         * Error message (if relevant)
         */
        std::optional<std::string> error;

        /**
         * A set of optional messages.
         * Among other use-cases, messages are used in the test cases.
         *
         * @ref testing
         */
        std::vector<std::string> messages;

        /**
         * Indicates to the CLI, if it should show the helper content.
         *
         * @ref helpers
         */
        bool showHelp = false;
    };

    /**
     * A definition of an option
     * To be used when defining the expected patterns of commands
     */
    struct DefineOption {
        /**
         * The internal ID (often identical to ``long_name``, but not required)
         * This is the ID you'll reference, when you want to handle information
         * provided by the end-user.
         */
        std::string id;

        /**
         * The single-character "short name". Given just as a letter, but reflects
         * e.g. ``-c`` or ``-V``.
         */
        std::optional<const char> short_name;

        /**
         * The long name of the option. Should be written without dashes.
         */
        std::optional<const char *> long_name;

        /**
         * Optional default value
         */
        std::optional<Value> defaultValue;

        /**
         * If set to true, and not provided by the end-user, then CLI will
         * treat it as an error.
         */
        bool required = false;

        /**
         * Specify the expected data type.
         */
        OptionDataType dataType = OptionDataType::Boolean;

        /**
         * Description for the helper.
         *
         * @ref helpers
         */
        std::string description;
    };

    /**
     * An interpreted argument.
     */
    struct Argument {
        /**
         * Argument value (always treated as string).
         */
        std::string value;
    };

    /**
     * An interpreted option.
     * For example --help or --name="John Doe"
     *
     * The `RawInput` is the value received in the console from the end-user.
     * ``mappedId`` signifies the ``id`` of the DefineOption which it has been mapped to.
     */
    struct Option {
        /**
         * The literal value received from the CLI argument list
         */
        std::string rawInput;

        /**
         * The ID of the DefineOption the option could be mapped to,
         * usually based on short_name or long_name
         */
        std::string mappedId;

        /**
         * The value
         */
        Value value;
    };
}
