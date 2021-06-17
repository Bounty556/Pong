#include "StringTests.h"

#include <Core/Logger.h>
#include <Core/String.h>
#include <Memory/MemoryManager.h>

#include "../TestMacros.h"

#include <utility>

void InitString()
{
	START_MEMORY_CHECK();

	Soul::String string1("This is a C-String.");

	ASSERT_EQUAL(string1[10], 'C', "Failed to store C-String.");
	ASSERT_EQUAL(string1.Length(), 19, "Incorrect C-String Length.");

	Soul::String string3("String 1");
	Soul::String string2(string3);

	ASSERT_EQUAL(string2[2], 'r', "Failed to copy string.");
	ASSERT_EQUAL(string2.Length(), string3.Length(), "Incorrect copy length.");
	ASSERT_EQUAL(string2.Length(), 8, "Incorrect copy length.");

	Soul::String string4("String 1");
	Soul::String string5(std::move(string4));

	ASSERT_EQUAL(string5[3], 'i', "Failed to move string.");
	ASSERT_EQUAL(string5.Length(), 8, "Incorrect move length.");

	END_MEMORY_CHECK();
}

void AssignString()
{
	START_MEMORY_CHECK();

	Soul::String string1;
	string1 = "This is a C-String.";

	ASSERT_EQUAL(string1[10], 'C', "Failed to store C-String.");
	ASSERT_EQUAL(string1.Length(), 19, "Incorrect C-String Length.");

	Soul::String string3("String 1");
	Soul::String string2;
	string2 = string3;

	ASSERT_EQUAL(string2[2], 'r', "Failed to copy string.");
	ASSERT_EQUAL(string2.Length(), string3.Length(), "Incorrect copy length.");
	ASSERT_EQUAL(string2.Length(), 8, "Incorrect copy length.");

	Soul::String string4("String 1");
	string2 = std::move(string4);

	ASSERT_EQUAL(string2[3], 'i', "Failed to move string.");
	ASSERT_EQUAL(string2.Length(), 8, "Incorrect move length.");

	END_MEMORY_CHECK();
}

void ConcatString()
{
	START_MEMORY_CHECK();

	Soul::String string1("This is ");
	const char* string2 = "a concatenated string.";
	// TODO: Soul::String string3(string1 + string2);

	//ASSERT_EQUAL(string3[4], ' ', "Failed to concatenate string1.");
	//ASSERT_EQUAL(string3[15], 't', "Failed to concatenate string2.");
	//ASSERT_EQUAL(string3.Length(), 30, "Incorrect concatenated length.");

	/*Soul::String string4("This is ");
	Soul::String string5 = "a concatenated string.";
	Soul::String string6(string4 + string5);

	ASSERT_EQUAL(string6[4], ' ', "Failed to concatenate string1.");
	ASSERT_EQUAL(string6[15], 't', "Failed to concatenate string2.");
	ASSERT_EQUAL(string6.Length(), 30, "Incorrect concatenated length.");*/

	END_MEMORY_CHECK();
}

void CompareStrings()
{
	START_MEMORY_CHECK();

	Soul::String string1("String A");
	Soul::String string2("String A");
	Soul::String string3("String B");

	ASSERT_TRUE(string1 == string2, "String equality failed.");
	ASSERT_TRUE(string1 != string3, "String inequality failed.");

	Soul::String string4("String A");
	const char* string5 = "String A";
	const char* string6 = "String B";

	ASSERT_TRUE(string4 == string5, "String equality failed.");
	ASSERT_TRUE(string4 != string6, "String inequality failed.");

	END_MEMORY_CHECK();
}

void CharCastString()
{
	START_MEMORY_CHECK();

	Soul::String string("Testing");

	ASSERT_EQUAL(string.Length(), 7, "String conversion failed.");

	END_MEMORY_CHECK();
}

void Substring()
{
	START_MEMORY_CHECK();

	// TODO:
	/*Soul::String string1("Testing");
	Soul::String string2(string1.Substring(2));
	Soul::String string3(string1.Substring(2, 3));

	ASSERT_EQUAL(string2[1], 't', "Substring construction failed.");
	ASSERT_EQUAL(string2.Length(), 5, "Substring construction failed.");
	ASSERT_EQUAL(string3[0], 's', "Substring construction failed.");
	ASSERT_EQUAL(string3.Length(), 1, "Substring construction failed.");*/

	END_MEMORY_CHECK();
}

void IndexOfChar()
{
	START_MEMORY_CHECK();

	// TODO:
	/*Soul::String string("testing");

	ASSERT_EQUAL(string.FindFirstOf('t'), 0, "Failed to find 't'.");
	ASSERT_EQUAL(string.FindFirstOf('i'), 4, "Failed to find 'i'.");
	ASSERT_EQUAL(string.FindFirstOf('x'), -1, "Found incorrect character.");*/

	END_MEMORY_CHECK();
}

void EditChar()
{
	START_MEMORY_CHECK();

	// TODO:
	/*Soul::String string("Testing");

	string[0] = 'R';

	ASSERT_EQUAL(string[0], 'R', "Failed to edit character in string.");*/

	END_MEMORY_CHECK();
}

void StringTests::RunAllTests()
{
	RUN_TEST(InitString);
	RUN_TEST(AssignString);
	RUN_TEST(ConcatString);
	RUN_TEST(CompareStrings);
	RUN_TEST(CharCastString);
	RUN_TEST(Substring);
	RUN_TEST(IndexOfChar);
}