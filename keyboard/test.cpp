#include <igloo/igloo.h>
#include "keyboard.h"

using namespace igloo;

Context(KEYBOARD){
    Spec(testName1) {
        int inputs = 0;
        auto result = keyboard(inputs);
        auto correct = 0;
        Assert::That(result, Equals(correct));
    }
    
    Spec(testName2) {
        int inputs = 0;
        auto result = keyboard(inputs);
        auto correct = 0;
        Assert::That(result, Equals(correct));
    }

    // EqualsWithDelta(value, allowedErrorAmount)
    // IsGreaterThan(value)     (verify actual is greater than value)
    // IsLessThan(value)        (verify actual is less than value)
    // strings: Contains("")  StartsWith("")  EndsWith("")  HasLength(int)
};

int main(int argc, const char* argv[]){
    return TestRunner::RunAllTests(argc, argv);
}
