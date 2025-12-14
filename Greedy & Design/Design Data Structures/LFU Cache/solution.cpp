#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

class LFUCache {
  struct Node {
    int key, value, freq;
    Node(int k, int v, int f) : key(k), value(v), freq(f) {}
  };

  int capacity;
  int minFreq;
  unordered_map<int, list<Node>::iterator> keyMap;
  unordered_map<int, list<Node>> freqMap;

public:
  LFUCache(int capacity) : capacity(capacity), minFreq(0) {}

  int get(int key) {
    if (capacity == 0 || keyMap.find(key) == keyMap.end())
      return -1;

    auto nodeIt = keyMap[key];
    int val = nodeIt->value;
    int freq = nodeIt->freq;

    // Remove from current freq list
    freqMap[freq].erase(nodeIt);
    if (freqMap[freq].empty()) {
      freqMap.erase(freq);
      if (minFreq == freq)
        minFreq++;
    }

    // Add to next freq list
    freqMap[freq + 1].emplace_front(key, val, freq + 1);
    keyMap[key] = freqMap[freq + 1].begin();
    return val;
  }

  void put(int key, int value) {
    if (capacity == 0)
      return;

    if (keyMap.find(key) != keyMap.end()) {
      keyMap[key]->value = value;
      get(key); // Promote
      return;
    }

    // Evict if full
    if (keyMap.size() == capacity) {
      int k = freqMap[minFreq].back().key;
      freqMap[minFreq].pop_back();
      if (freqMap[minFreq].empty())
        freqMap.erase(minFreq);
      keyMap.erase(k);
    }

    // Insert new
    minFreq = 1;
    freqMap[1].emplace_front(key, value, 1);
    keyMap[key] = freqMap[1].begin();
  }
};

int main() {
  LFUCache lfu(2);
  lfu.put(1, 1);
  lfu.put(2, 2);
  cout << "Get 1 (Expect 1): " << lfu.get(1) << endl;
  lfu.put(3, 3);
  cout << "Get 2 (Expect -1): " << lfu.get(2) << endl;
  cout << "Get 3 (Expect 3): " << lfu.get(3) << endl;
  lfu.put(4, 4);
  // 1 and 3 are both Freq 2. 1 was promoted first, so 1 is LRU. Evict 1.
  cout << "Get 1 (Expect -1): " << lfu.get(1) << endl;
  cout << "Get 3 (Expect 3): " << lfu.get(3) << endl;
  cout << "Get 4 (Expect 4): " << lfu.get(4) << endl;
  return 0;
}
