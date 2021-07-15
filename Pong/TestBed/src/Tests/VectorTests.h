#pragma once

#include "ITestSuite.h"

class VectorTests : public ITestSuite
{
public:
	virtual void RunAllTests() override;
};