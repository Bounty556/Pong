#pragma once

#include "ITestSuite.h"

class UITests : public ITestSuite
{
public:
	virtual void RunAllTests() override;
};