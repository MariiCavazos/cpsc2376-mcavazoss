#include "pch.h"
#include "CppUnitTest.h"
#include "../../practice/practice03/practice03.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace practice03_test
{
    TEST_CLASS(SumRangeTests)
    {
    public:

        TEST_METHOD(SumRange_NormalRange)
        {
            Assert::AreEqual(15, MathUtils::sumRange(1, 5)); // 1+2+3+4+5
        }

        TEST_METHOD(SumRange_SameStartEnd)
        {
            Assert::AreEqual(5, MathUtils::sumRange(5, 5)); // Only 5
        }

        TEST_METHOD(SumRange_InvalidRange)
        {
            Assert::AreEqual(0, MathUtils::sumRange(10, 5)); // start > end
        }
    };

    TEST_CLASS(ContainsNegativeTests)
    {
    public:

        TEST_METHOD(ContainsNegative_HasNegative)
        {
            std::vector<int> values = { 1, -3, 2 };
            Assert::IsTrue(MathUtils::containsNegative(values));
        }

        TEST_METHOD(ContainsNegative_AllPositive)
        {
            std::vector<int> values = { 1, 2, 3 };
            Assert::IsFalse(MathUtils::containsNegative(values));
        }

        TEST_METHOD(ContainsNegative_EmptyList)
        {
            std::vector<int> values = {};
            Assert::IsFalse(MathUtils::containsNegative(values));
        }
    };

    TEST_CLASS(FindMaxTests)
    {
    public:

        TEST_METHOD(FindMax_NormalList)
        {
            std::vector<int> values = { 1, 5, 3, 7, 2 };
            Assert::AreEqual(7, MathUtils::findMax(values));
        }

        TEST_METHOD(FindMax_AllSameValues)
        {
            std::vector<int> values = { 4, 4, 4, 4 };
            Assert::AreEqual(4, MathUtils::findMax(values));
        }

        TEST_METHOD(FindMax_ThrowsOnEmptyList)
        {
            std::vector<int> values = {};
            try {
                MathUtils::findMax(values);
                Assert::Fail(L"Expected exception not thrown.");
            }
            catch (const std::invalid_argument& e) {
                Assert::AreEqual("Empty vector provided to findMax.", e.what());
            }
            catch (...) {
                Assert::Fail(L"Unexpected exception type thrown.");
            }
        }
    };
}