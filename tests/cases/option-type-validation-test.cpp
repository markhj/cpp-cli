#include "cpp-cli/cpp-cli.hpp"
#include "base-test.hpp"

using CppCLI::CLI;
using CppCLI::Subcommand;
using CppCLI::Interpretation;
using CppCLI::Response;
using CppCLI::ResponseState;
using CppCLI::Value;

class OptionTypeValidationTest : public BaseTestCase {
public:
    OptionTypeValidationTest() : BaseTestCase() {}

    void configure(CLI &cli) override {
        m_cli.define(
                Subcommand()
                        .addOption({
                                           .id = "bool",
                                           .short_name = 'b',
                                           .long_name = "bool",
                                           .dataType = OptionDataType::Boolean,
                                   })
                        .addOption({
                                           .id = "string",
                                           .short_name = 's',
                                           .long_name = "string",
                                           .dataType = OptionDataType::String,
                                   })
                        .handle([](const ConsoleIO &emitter, const Interpretation &interpretation) {
                            return Response();
                        })
        );
    }

    void run() override {
        testCmd("-b -sHello", [&](const Response &response) {
            assertEquals(ResponseState::Success, response.state);
        });

        testCmd("-bHello", [&](const Response &response) {
            assertEquals(ResponseState::Error, response.state);
            assertEquals("b must be boolean.", response.error.value());
        });

        testCmd("-s", [&](const Response &response) {
            assertEquals(ResponseState::Error, response.state);
            assertEquals("s must be string.", response.error.value());
        });

        testCmd("--bool=Hello", [&](const Response &response) {
            assertEquals(ResponseState::Error, response.state);
            assertEquals("bool must be boolean.", response.error.value());
        });

        testCmd("--string", [&](const Response &response) {
            assertEquals(ResponseState::Error, response.state);
            assertEquals("string must be string.", response.error.value());
        });
    }
};
