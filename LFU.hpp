#include <iostream>
#include <list>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <iterator>

class LFU
{
private:

	using map = std::unordered_map<int, std::pair<int, std::list<int>::iterator>>;
	using list = std::list<int>;
	using cache_it = std::list<int>::iterator;

	size_t mCapacity;
	size_t  mSize = 0;
	map mHash_table;
	list mCache;

public:

	LFU(size_t a) {mCapacity = a;}

	LFU() {mCapacity = 0;}

	void lowFrequency_to_front(cache_it it)
	{
		cache_it it_next = it;
		it_next++;

		int a = *it;
		int b = *it_next;

		if (it_next != mCache.end() && mHash_table[a].first > mHash_table[b].first)
		{
			mCache.splice(it, mCache, it_next);
		}
	}

	void page_insertion(int key)
	{
		mCache.push_front(key);
		mHash_table[key] = {1, mCache.begin()};
	}
	
	int LFU_insert(int key)
	{
		int hits = 0;

		if (mHash_table.find(key) != mHash_table.end())
		{
			mHash_table[key].first += 1;
			hits++;

			lowFrequency_to_front(mHash_table[key].second);
		}
		else
		{
			if (mSize != mCapacity)
			{
				page_insertion(key);

				mSize++;
			}
			else
			{
				mHash_table.erase(*mCache.begin());
				mCache.pop_front();

				page_insertion(key);
			}
		}
		return hits;
	}
};

