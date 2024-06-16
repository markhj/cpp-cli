#include "cpp-cli/cpp-cli.hpp"
#include "base-test.hpp"

using CppCLI::CLI;
using CppCLI::Subcommand;
using CppCLI::Interpretation;
using CppCLI::Response;
using CppCLI::ResponseState;
using CppCLI::Value;

class DefaultValuesTest : public BaseTestCase {
public:
    DefaultValuesTest() : BaseTestCase() {}

    void configure(CLI &cli) override {
        m_cli.define(
                Subcommand()
                        .addOption({"no-def", 'n', "no-def"})
                        .addOption({
                                           .id = "def",
                                           .short_name = 'd',
                                           .long_name = "def",
                                           .defaultValue = Value("Default Value"),
                                           .dataType = OptionDataType::String,
                                   })
                        .addOption({"def-false", 'f', "def-false", Value(false)})
                        .addOption({"def-true", 't', "def-true", Value(true)})
                        .addOption({
                                           .id = "set-me",
                                           .short_name = 's',
                                           .long_name = "set-me",
                                           .defaultValue = Value("Fallback"),
                                           .dataType = OptionDataType::String,
                                   })
                        .handle([](const ConsoleIO &emitter, const Interpretation &interpretation) {
                            Response response;
                            auto opts = interpretation.getOptions();
                            response.messages.push_back(opts[1].value.getAsString());
                            response.messages.emplace_back(opts[2].value.getAsBool() ? "1" : "0");
                            response.messages.emplace_back(opts[3].value.getAsBool() ? "1" : "0");
                            response.messages.push_back(opts[0].value.getAsString());
                            return response;
                        })
        );
    }

    void run() override {
        testCmd("--set-me=Override", [&](const Response &response) {
            assertEquals(ResponseState::Success, response.state);
            assertEquals("Default Value", response.messages[0]);
            assertEquals("0", response.messages[1]);
            assertEquals("1", response.messages[2]);
            assertEquals("Override", response.messages[3]);
        });

        // Short name test
        testCmd("-sOverride", [&](const Response &response) {
            assertEquals(ResponseState::Success, response.state);
            assertEquals("Default Value", response.messages[0]);
        });

    }
};
