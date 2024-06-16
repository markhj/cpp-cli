#include "cpp-cli/utilities/value.hpp"
#include <cassert>

CppCLI::OptionDataType CppCLI::Value::getDataType() const noexcept {
    return m_dataType;
}
bool CppCLI::Value::getAsBool() const {
    assert(m_dataType == OptionDataType::Boolean && "Only boolean data types can use getAsBool");

    return m_boolVal;
}

std::string CppCLI::Value::getAsString() const {
    return m_strVal;
}