#pragma once
#include "Platform.h"

namespace CustomMath{

	static int32 Fibonacci(int32 num)
	{
		if (num <= 0)
		{
			return 0;
		}
		else if (num == 1 || num == 2)
		{
			return 1;
		}
		else
		{
			return (Fibonacci(num - 1) + Fibonacci(num - 2));
		}
	}

}