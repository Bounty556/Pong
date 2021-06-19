#pragma once

#include "ITestSuite.h"

class QueueTests : public ITestSuite
{
public:
	virtual void RunAllTests() override;
};