#pragma once

#include "ITestSuite.h"

class MessageBusTests : public ITestSuite
{
public:
	virtual void RunAllTests() override;
};