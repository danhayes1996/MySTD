#pragma once

#include <chrono>

namespace mystd {

	struct timer
	{
		std::chrono::time_point<std::chrono::steady_clock> start;

		Timer() 
		{
			start = std::chrono::high_resolution_clock::now();
		}

		void reset()
		{
			start = std::chrono::high_resolution_clock::now();
		}

		float timeElapsed()
		{
			std::chrono::duration<float> duration = std::chrono::high_resolution_clock::now() - start;

			return duration.count();
		}
	};
}