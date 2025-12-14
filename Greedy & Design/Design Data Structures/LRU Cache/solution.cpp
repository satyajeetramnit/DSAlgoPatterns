#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>

using namespace std;

class LRUCache {
  struct Node {
    int key;
    int value;
    Node(int k, int v) : key(k), value(v) {}
  };

  int capacity;
  list<Node> cacheList; // MRU at front, LRU at back
  unordered_map<int, list<Node>::iterator> cacheMap;

public:
  LRUCache(int capacity) : capacity(capacity) {}

  int get(int key) {
    if (cacheMap.find(key) == cacheMap.end()) {
      return -1; // Not found
    }
    // Move to front (MRU)
    cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
    return cacheMap[key]->value;
  }

  void put(int key, int value) {
    if (cacheMap.find(key) != cacheMap.end()) {
      // Update existing
      cacheMap[key]->value = value;
      cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
      return;
    }

    // Evict if full
    if (cacheList.size() == capacity) {
      int lruKey = cacheList.back().key;
      cacheList.pop_back();
      cacheMap.erase(lruKey);
    }

    // Insert new
    cacheList.emplace_front(key, value);
    cacheMap[key] = cacheList.begin();
  }
};

int main() {
  LRUCache lRUCache(2);
  lRUCache.put(1, 1); // cache is {1=1}
  lRUCache.put(2, 2); // cache is {1=1, 2=2}
  cout << "Get 1 (Expect 1): " << lRUCache.get(1) << endl; // return 1
  lRUCache.put(3,
               3); // LRU key was 2, evicts key 2? Wait. Order was 2->1. Get(1)
                   // made 1 MRU. So 2 is LRU. Evicts 2, cache is {1=1, 3=3}
  cout << "Get 2 (Expect -1): " << lRUCache.get(2)
       << endl;       // returns -1 (not found)
  lRUCache.put(4, 4); // LRU is 1. Evicts 1. cache is {4=4, 3=3}
  cout << "Get 1 (Expect -1): " << lRUCache.get(1)
       << endl; // return -1 (not found)
  cout << "Get 3 (Expect 3): " << lRUCache.get(3) << endl; // return 3
  cout << "Get 4 (Expect 4): " << lRUCache.get(4) << endl; // return 4
  return 0;
}
