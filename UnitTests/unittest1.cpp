#include "stdafx.h"
#include "CppUnitTest.h"
#include "../FizzBuzz/StringChecks.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestBasicCase)
		{
			Assert::IsTrue(StringChecks::AInB("agua", "agua")); //Same string
			Assert::IsFalse(StringChecks::AInB("agua", "eeeeeeee")); //Different string
			Assert::IsTrue(StringChecks::AInB("agua", "naguan")); //String in the middle
			Assert::IsTrue(StringChecks::AInB("agua", " aguaa")); //Extra character at the end
			Assert::IsFalse(StringChecks::AInB("agua", "naagun")); //String not inside
		}
		TEST_METHOD(TestNumbers)
		{
			Assert::IsFalse(StringChecks::AInB("agua1", "nagua")); //Number check fasle
			Assert::IsTrue(StringChecks::AInB("agua1", "nagua1")); //Number check true
			Assert::IsTrue(StringChecks::AInB("4453", "18374453")); //Number check true
			Assert::IsFalse(StringChecks::AInB("4453", "4653")); //Number check true
		}
		TEST_METHOD(TestSpaces)
		{
			Assert::IsTrue(StringChecks::AInB("ag ua", " ag uaa"));
			Assert::IsFalse(StringChecks::AInB("agua", " ag uaa"));
			Assert::IsTrue(StringChecks::AInB("445 3", "ff445 3afd")); //Number check true
		}
		TEST_METHOD(TestRepetition)
		{
			Assert::IsTrue(StringChecks::AInB("ab", " aabg uab")); //Repetition
			Assert::IsFalse(StringChecks::AInB("ba", " aabg uab")); //Repetition
		}
		TEST_METHOD(TestUperLowerCase)
		{
			Assert::IsTrue(StringChecks::AInB("Agua", "naguan"));
			Assert::IsTrue(StringChecks::AInB("AGUA", "naguan"));
			Assert::IsTrue(StringChecks::AInB("agua", "nAGUan"));
			Assert::IsTrue(StringChecks::AInB("agua", "nAGUA"));
			Assert::IsFalse(StringChecks::AInB("agua", "nAGU"));
		}
		TEST_METHOD(TestOrdering)
		{
			Assert::IsTrue(StringChecks::AInBDisordered("Agua", "naagun"));
			Assert::IsTrue(StringChecks::AInBDisordered("AGUA", "naagun"));
			Assert::IsTrue(StringChecks::AInBDisordered("agua", "nugaan"));
			Assert::IsFalse(StringChecks::AInBDisordered("agua", "nuganan"));
			Assert::IsTrue(StringChecks::AInBDisordered("agua", "nAGUA"));
			Assert::IsTrue(StringChecks::AInBDisordered("agua", "aaaaaaagu"));
			Assert::IsTrue(StringChecks::AInBDisordered("agua", "uuguaa"));
			Assert::IsTrue(StringChecks::AInBDisordered("agu a", "uug uaa"));
		}
	};
}