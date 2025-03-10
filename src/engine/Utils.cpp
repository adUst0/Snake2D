#include <random>

int randRanged(int min, int max)
{
	static std::mt19937 s_random_engine(std::random_device{}());

	std::uniform_int_distribution<int> dis(min, max);
	return dis(s_random_engine);
}