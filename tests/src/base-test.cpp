#include "base-test.hpp"

void BaseTestCase::testCmd(const std::string &cmd,
                           const std::function<void(const Response&)>& assertions) {
    simulateCmd(cmd, [&](int argc, char *argv[]) {
        assertions(m_cli.run(argc, argv));
    });
}

void BaseTestCase::test() {
    configure(m_cli);
    run();
}
