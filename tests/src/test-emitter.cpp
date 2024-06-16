#include "test-emitter.hpp"

void TestEmitter::emit(const std::string &msg) noexcept {
    m_messages.push_back(msg);
}

std::vector<std::string> TestEmitter::getMessage() const {
    return m_messages;
}

void TestEmitter::error(const std::string &msg) noexcept {
    m_messages.push_back(msg);
}
