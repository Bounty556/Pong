#pragma once

#include "ITestSuite.h"

class NodeTests : public ITestSuite
{
public:
	virtual void RunAllTests() override;
};