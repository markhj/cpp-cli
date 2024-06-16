#include "cpp-cli/cpp-cli.hpp"
#include "base-test.hpp"

using CppCLI::CLI;
using CppCLI::Subcommand;
using CppCLI::Interpretation;
using CppCLI::Response;
using CppCLI::ResponseState;
using CppCLI::Value;

class BoolCastTest : public BaseTestCase {
public:
    BoolCastTest() : BaseTestCase() {}

    void configure(CLI &cli) override {
        m_cli.define(
                Subcommand()
                        .addOption({
                                           .id = "value",
                                           .short_name = 'v',
                                   })
                        .handle([](const ConsoleIO &emitter, const Interpretation &interpretation) {
                            Response response;
                            response.messages.emplace_back(
                                    interpretation.getOptions()[0].value.getAsBool() ? "1" : "0");
                            return response;
                        })
        );
    }

    void run() override {
        testCmd("--v", [&](const Response &response) {
            assertEquals("1", response.messages[0]);
        });

        testCmd("-v", [&](const Response &response) {
            assertEquals("1", response.messages[0]);
        });
    }
};
