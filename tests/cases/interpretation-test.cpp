#include "cpp-cli/cpp-cli.hpp"
#include "base-test.hpp"

using CppCLI::Interpretation;
using CppCLI::Interpreter;
using CppCLI::OptionDataType;

class InterpretationTest : public BBUnit::TestCase,
                           public TestTools {
public:
    void test() {
        boolFlags();
        stringOptions();
        initialArgs();
    }

    void boolFlags() {
        cmd(R"(--version -d")", [&](const Interpretation& result) {
            assertFalse(result.getSubcommand().has_value());

            std::vector<Option> options = result.getOptions();
            assertCount<Option>(2, options);

            assertOptionBool(options[0], "version", true);
            assertOptionBool(options[1], "d", true);
        });
    }

    void stringOptions() {
        cmd(R"(--opt=value --a="Value A" -fName -l"Last name")", [&](const Interpretation& result) {
            assertFalse(result.getSubcommand().has_value());

            std::vector<Option> options = result.getOptions();
            assertCount<Option>(4, options);

            assertOptionStr(options[0], "opt", "value");
            assertOptionStr(options[1], "a", "Value A");
            assertOptionStr(options[2], "f", "Name");
            assertOptionStr(options[3], "l", "Last name");
        });
    }

    void initialArgs() {
        cmd(R"(a b --c)", [&](const Interpretation& result) {
            std::vector<Argument> initialArgumentList = result.getInitialArgumentList();
            assertCount<Argument>(2, initialArgumentList);
            assertEquals("a", initialArgumentList[0].value);
            assertEquals("b", initialArgumentList[1].value);
        });
    }

    void assertOptionBool(const Option& option, const std::string& id, bool value) {
        assertEquals(id, option.rawInput);
        assertEquals(OptionDataType::Boolean, option.value.getDataType());
        assertEquals(value, option.value.getAsBool());
    }

    void assertOptionStr(const Option& option, const std::string& id, const std::string& value) {
        assertEquals(id, option.rawInput);
        assertEquals(OptionDataType::String, option.value.getDataType());
        assertEquals(value, option.value.getAsString());
    }

    void cmd(const std::string &cmd, const std::function<void(const Interpretation& result)>& assertions) {
        simulateCmd(cmd, [&](int argc, char *argv[]) {
            assertions(Interpreter::interpret(argc, argv));
        });
    }
};
