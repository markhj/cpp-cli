#pragma once

namespace CppCLI {
    /**
     * Supported data types to be used when interpreting the CLI inputs,
     * as well as used in DefineOption to specify expectations.
     */
    enum OptionDataType {
        Boolean,
        String,
    };

    /**
     * The outcome of a subcommand's handle method.
     */
    enum ResponseState {
        Success,
        Error,
    };
}
