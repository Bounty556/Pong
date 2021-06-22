#pragma once

#include "ITestSuite.h"

class CollisionTests : public ITestSuite
{
public:
	virtual void RunAllTests() override;
};