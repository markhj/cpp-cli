#include "cpp-cli/cpp-cli.hpp"
#include "base-test.hpp"

using CppCLI::CLI;
using CppCLI::Subcommand;
using CppCLI::Interpretation;
using CppCLI::Response;
using CppCLI::ResponseState;
using CppCLI::Value;

class NonExistingOptionsTest : public BaseTestCase {
public:
    NonExistingOptionsTest() : BaseTestCase() {}

    void configure(CLI &cli) override {
        m_cli.define(
                Subcommand()
                        .addOption({"existing", 'e', "existing"})
                        .handle([](const ConsoleIO &emitter, const Interpretation &interpretation) {
                            return Response();
                        })
        );
    }

    void run() override {
        testCmd("--existing", [&](const Response& response) {
            assertEquals(ResponseState::Success, response.state);
        });

        testCmd("--fake", [&](const Response& response) {
            assertEquals(ResponseState::Error, response.state);
            assertEquals("Unknown option: fake", response.error.value());
        });
    }
};
