#include <iostream>
#include "LFU.hpp"

int main()
{
	size_t capacity;
	std::cin >> capacity;
	LFU cache(capacity);

	int amount;
	std::cin >> amount;

	int hits = 0;
	for (int i = 0; i < amount; i++)
	{
		int page;
		std::cin >> page;

		hits += cache.LFU_insert(page);
	}
	std::cout << hits << std::endl;
}