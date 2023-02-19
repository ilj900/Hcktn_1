#pragma once

#include "canvas.h"

#include <memory>

class FApplication
{
public:
	FApplication();
	int Run();

private:
	std::shared_ptr<FCanvas> Canvas;
	
};