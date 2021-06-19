#pragma once

#include "ITestSuite.h"

class MapTests : public ITestSuite
{
public:
	virtual void RunAllTests() override;
};