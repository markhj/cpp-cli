#include "cpp-cli/cpp-cli.hpp"
#include "base-test.hpp"

using CppCLI::CLI;
using CppCLI::Subcommand;
using CppCLI::Interpretation;
using CppCLI::Response;
using CppCLI::ResponseState;
using CppCLI::Value;

class RequiredValuesTest : public BaseTestCase {
public:
    RequiredValuesTest() : BaseTestCase() {}

    void configure(CLI &cli) override {
        m_cli.define(
                Subcommand()
                        .addOption({"not-required", 'n', "not-required"})
                        .addOption({
                            .id = "required",
                            .short_name = 'r',
                            .long_name = "required",
                            .required = true,
                        })
                        .handle([](const ConsoleIO &emitter, const Interpretation &interpretation) {
                            return Response();
                        })
        );
    }

    void run() override {
        testCmd("--required", [&](const Response& response) {
            assertEquals(ResponseState::Success, response.state);
        });

        testCmd("--r", [&](const Response& response) {
            assertEquals(ResponseState::Success, response.state);
        });

        testCmd("", [&](const Response& response) {
            assertEquals(ResponseState::Error, response.state);
            assertEquals("Required option not provided: required", response.error.value());
        });
    }
};
