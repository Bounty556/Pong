#pragma once

#include "ITestSuite.h"

class MathTests : public ITestSuite
{
public:
	virtual void RunAllTests() override;
};