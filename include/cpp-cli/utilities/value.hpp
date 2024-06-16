#pragma once

#include "cpp-cli/misc/enums.hpp"
#include <string>

namespace CppCLI {
    /**
     * Handles a number of different values, which can be provided by the CLI,
     * and expected by DefineOption.
     */
    class Value {
    public:
        /**
         * Set a boolean value.
         *
         * @param value
         */
        explicit Value(bool value) :
                m_boolVal(value),
                m_dataType(OptionDataType::Boolean) {}

        /**
         * Set a string value.
         *
         * @param value
         */
        explicit Value(std::string value) :
                m_strVal(std::move(value)),
                m_dataType(OptionDataType::String) {}

        /**
         * Set a const char* (acting as string)
         *
         * @param value
         */
        explicit Value(const char* value) :
                m_strVal(value),
                m_dataType(OptionDataType::String) {}

        /**
         * Get the data type
         *
         * @return
         */
        [[nodiscard]] OptionDataType getDataType() const noexcept;

        /**
         * Get the value (safely as boolean)
         *
         * @return
         */
        [[nodiscard]] bool getAsBool() const;

        /**
         * The the value as string.
         *
         * @return
         */
        [[nodiscard]] std::string getAsString() const;

    private:
        OptionDataType m_dataType;
        bool m_boolVal = false;
        std::string m_strVal;
    };
};
