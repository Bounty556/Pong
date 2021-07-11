#pragma once

#include "ITestSuite.h"

class INodeTests : public ITestSuite
{
public:
	virtual void RunAllTests() override;
};