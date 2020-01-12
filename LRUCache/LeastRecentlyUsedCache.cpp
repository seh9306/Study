#include <assert.h>
#include <unordered_map>
#include <deque>

// Least Recently Used cache
class LRUCache {
public:
	LRUCache(int capacity) : capacity_(capacity) { }

	int Get(int key) {
		const auto& value = cacheMap_.find(key);
		if (value != cacheMap_.end()) {
			for (auto it = cacheDeque_.begin(); it != cacheDeque_.end(); ++it) {
				if (value->second == it->second) {
					cacheDeque_.erase(it);
					break;
				}
			}
			cacheDeque_.push_front({ value->first, value->second });
			return value->second;
		}

		return -1;
	}

	void Put(int key, int value) {
		if (capacity_ == cacheDeque_.size()) {
			auto& del = cacheDeque_.at(cacheDeque_.size() - 1);
			cacheDeque_.pop_back();
			cacheMap_.erase(del.first);
		}

		cacheDeque_.push_front({ key, value });
		cacheMap_[key] = value;
	}

private:
	int capacity_;
	std::unordered_map<int, int> cacheMap_;
	std::deque<std::pair<int,int>> cacheDeque_;
};

int main() {
	LRUCache cache(2);

	cache.Put(1, 1);
	cache.Put(2, 2);
	assert(1 == cache.Get(1));
	cache.Put(3, 3);
	assert(-1 == cache.Get(2));
	assert(3 == cache.Get(3));
}