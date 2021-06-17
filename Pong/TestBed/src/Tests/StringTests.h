#pragma once

#include "ITestSuite.h"

class StringTests : public ITestSuite
{
public:
	virtual void RunAllTests() override;
};