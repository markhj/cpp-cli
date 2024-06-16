#include "cpp-cli/cpp-cli.hpp"
#include "base-test.hpp"

using CppCLI::CLI;
using CppCLI::Subcommand;
using CppCLI::Interpretation;
using CppCLI::Response;
using CppCLI::ResponseState;

class UniversalCommandTest : public BaseTestCase {
public:
    UniversalCommandTest() : BaseTestCase() {}

    void configure(CLI &cli) override {
        m_cli.define(
                Subcommand()
                        .addOption({"help", 'h', "help"})
                        .addOption({"version", 'v', "version"})
                        .handle([](const ConsoleIO &emitter, const Interpretation &interpretation) {
                            Response response;
                            response.messages.emplace_back("Hello!");
                            return response;
                        })
        );
    }

    void run() override {
        testCmd("--version", [&](const Response& response) {
            assertEquals(ResponseState::Success, response.state);
        });

        testCmd("false-subcommand", [&](const Response& response) {
            assertEquals(ResponseState::Error, response.state);
            assertTrue(response.error.has_value());
            assertEquals("Unknown command.", response.error.value());
        });

        testCmd("", [&](const Response& response) {
            assertEquals(ResponseState::Success, response.state);
        });
    }
};
