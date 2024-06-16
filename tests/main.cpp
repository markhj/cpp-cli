#include <bbunit/bbunit.hpp>

#include "cases/universal-command-test.cpp"
#include "cases/interpretation-test.cpp"
#include "cases/default-values-test.cpp"
#include "cases/required-values-test.cpp"
#include "cases/option-type-validation-test.cpp"
#include "cases/non-existing-options.cpp"
#include "cases/bool-cast-test.cpp"
#include "cases/subcmd-tree-test.cpp"

int main() {
    BBUnit::TestSuite<InterpretationTest> interpretation(&InterpretationTest::test);
    BBUnit::TestSuite<UniversalCommandTest> universalCommands(&UniversalCommandTest::test);
    BBUnit::TestSuite<DefaultValuesTest> defaultValues(&DefaultValuesTest::test);
    BBUnit::TestSuite<RequiredValuesTest> requiredValues(&RequiredValuesTest::test);
    BBUnit::TestSuite<OptionTypeValidationTest> optionTypeValidation(&OptionTypeValidationTest::test);
    BBUnit::TestSuite<NonExistingOptionsTest> nonExistingOptions(&NonExistingOptionsTest::test);
    BBUnit::TestSuite<BoolCastTest> boolCast(&BoolCastTest::test);
    BBUnit::TestSuite<SubcommandTreeTest> subcommandTree(&SubcommandTreeTest::test);

    BBUnit::TestRunner().run(
            interpretation,
            universalCommands,
            defaultValues,
            requiredValues,
            optionTypeValidation,
            nonExistingOptions,
            boolCast,
            subcommandTree
            );


    return 0;
}
