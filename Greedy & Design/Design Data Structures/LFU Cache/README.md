# LFU Cache

## 🧩 Problem Statement
Design and implement a data structure for a **Least Frequently Used (LFU)** cache.

Implement the `LFUCache` class:
- `LFUCache(int capacity)` Initializes the object with the `capacity` of the data structure.
- `int get(int key)` Gets the value of the `key` if the `key` exists in the cache. Otherwise, returns `-1`.
- `void put(int key, int value)` Update the value of the `key` if present, or inserts the `key` if not already present. When the cache reaches its `capacity`, it should invalidate and remove the **least frequently used** key before inserting a new item. For this problem, when there is a **tie** (i.e., two or more keys have the same frequency), the **least recently used** key would be invalidated.

To determine the least frequently used key, a **use counter** is maintained for each key in the cache. The key with the smallest use counter is the least frequently used key.

The functions `get` and `put` must each run in $O(1)$ average time complexity.

## 🔍 Approaches

### 1. Two Hash Maps + Frequency Lists ($O(1)$)
- **Concept:** We need to group keys by their frequency so we can find the `min_freq` group instantly. Within each group, we need LRU order to break ties.
- **Structure:**
  - **Node Maps (`key -> Node`):** To access content and metadata (frequency).
  - **Frequency Map (`freq -> Doubly Linked List`):** Each frequency bucket holds a list of nodes with that frequency. The list maintains time-ordering (Tail = LRU for that freq).
  - **Min Frequency (`minFreq`):** Iterate-able pointer to the lowest non-empty frequency bucket.
- **Operations:**
  - `get(key)`:
    - Locate Node.
    - Remove Node from `freq` list.
    - Increment Node frequency.
    - Add Node to `freq + 1` list.
    - If `freq` list is empty and `freq == minFreq`, increment `minFreq`.
  - `put(key, value)`:
    - If key exists: Update value, call `get(key)` logic to increment freq.
    - If new:
      - If full: Get list at `minFreq`. Remove LRU (tail). Delete from key map.
      - Create new Node with `freq = 1`.
      - Add to `freq = 1` list.
      - `minFreq = 1`.

### 🏛️ Design Diagram
```mermaid
graph TD
    subgraph Metadata
        m[minFreq: 1]
    end

    subgraph KeyMap
        k1[Key: A] -->|Ptr| n1
        k2[Key: B] -->|Ptr| n2
        k3[Key: C] -->|Ptr| n3
    end

    subgraph FrequencyMap
        direction TB
        f1[Freq: 1] -->|Head| l1_head((Head))
        l1_head <--> n3[Node C (Freq 1)] <--> l1_tail((Tail))
        
        f2[Freq: 2] -->|Head| l2_head((Head))
        l2_head <--> n1[Node A (Freq 2)] <--> n2[Node B (Freq 2)] <--> l2_tail((Tail))
    end

    n3 -.->|Next Access| f2
    style m fill:#ff9800,stroke:#333
    style n1 fill:#4caf50,stroke:#333
    style n3 fill:#2196f3,stroke:#333
```

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(1)$ for both operations.
- **Space Complexity:** $O(N)$.

## 🚀 Code Implementations

### C++
```cpp
#include <unordered_map>
#include <list>
#include <iostream>

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
        if (capacity == 0 || keyMap.find(key) == keyMap.end()) return -1;

        auto nodeIt = keyMap[key];
        int val = nodeIt->value;
        int freq = nodeIt->freq;

        // Remove from current freq list
        freqMap[freq].erase(nodeIt);
        if (freqMap[freq].empty()) {
            freqMap.erase(freq);
            if (minFreq == freq) minFreq++;
        }

        // Add to next freq list
        freqMap[freq + 1].emplace_front(key, val, freq + 1);
        keyMap[key] = freqMap[freq + 1].begin();
        return val;
    }

    void put(int key, int value) {
        if (capacity == 0) return;

        if (keyMap.find(key) != keyMap.end()) {
            // Update value and freq
            auto nodeIt = keyMap[key];
            nodeIt->value = value; // Update value in place before move? Actually safer to remove/add.
            get(key); // Reuses the promotion logic
            // Wait, get(key) returns value. We need to update value.
            // Simplified: Update the value in the NEW node. 
            // Correct flow: get(key) promotes it. The logic above updates val. But get() reads OLD val.
            // Let's refine manual update:
            // Actually, we can just update the iterator's value then call get() logic or copy-paste.
             keyMap[key]->value = value; // Update value
             // Now promote
             get(key); // This promotes and returns the new value. Safe.
             return;
        }

        // Evict if full
        if (keyMap.size() == capacity) {
            // Remove from minFreq list (LRU is at back)
            int k = freqMap[minFreq].back().key;
            freqMap[minFreq].pop_back();
            if (freqMap[minFreq].empty()) freqMap.erase(minFreq);
            keyMap.erase(k);
        }

        // Insert new
        minFreq = 1;
        freqMap[1].emplace_front(key, value, 1);
        keyMap[key] = freqMap[1].begin();
    }
};
```

### Python
```python
from collections import defaultdict, OrderedDict

class Node:
    def __init__(self, key, val, freq=1):
        self.key = key
        self.val = val
        self.freq = freq

class LFUCache:
    def __init__(self, capacity: int):
        self.capacity = capacity
        # Key -> Node
        self.key_map = {} 
        # Freq -> OrderedDict (acts as Doubly Linked List)
        self.freq_map = defaultdict(OrderedDict) 
        self.min_freq = 0

    def _update(self, node):
        # Remove from current freq bucket
        freq = node.freq
        del self.freq_map[freq][node.key]
        
        if not self.freq_map[freq]:
            del self.freq_map[freq]
            if self.min_freq == freq:
                self.min_freq += 1
        
        # Add to next freq bucket
        node.freq += 1
        self.freq_map[node.freq][node.key] = node

    def get(self, key: int) -> int:
        if key not in self.key_map:
            return -1
        node = self.key_map[key]
        self._update(node)
        return node.val

    def put(self, key: int, value: int) -> None:
        if self.capacity == 0:
            return

        if key in self.key_map:
            node = self.key_map[key]
            node.val = value
            self._update(node)
        else:
            if len(self.key_map) == self.capacity:
                # Evict from min_freq
                # OrderedDict popitem(last=False) pops the FIRST item (FIFO/LRU depending on insert)
                # We insert new items usually. Wait.
                # In Python OrderedDict:
                # If we just add items, they go to the end.
                # If we treat End as MRU, then Front is LRU.
                # popitem(last=False) removes Front (LRU).
                # Yes.
                k, _ = self.freq_map[self.min_freq].popitem(last=False)
                del self.key_map[k]
                if not self.freq_map[self.min_freq]:
                    del self.freq_map[self.min_freq]
            
            # Insert new
            self.min_freq = 1
            node = Node(key, value)
            self.key_map[key] = node
            self.freq_map[1][key] = node
```

### Java
```java
import java.util.HashMap;
import java.util.Map;

class LFUCache {
    class Node {
        int key, value, freq;
        Node prev, next;
        Node(int k, int v) {
            key = k;
            value = v;
            freq = 1;
        }
    }

    class DLList {
        Node head, tail;
        int size;
        DLList() {
            head = new Node(0, 0);
            tail = new Node(0, 0);
            head.next = tail;
            tail.prev = head;
        }
        void addHead(Node node) {
            node.next = head.next;
            node.prev = head;
            head.next.prev = node;
            head.next = node;
            size++;
        }
        void remove(Node node) {
            node.prev.next = node.next;
            node.next.prev = node.prev;
            size--;
        }
        Node removeTail() {
            if (size > 0) {
                Node node = tail.prev;
                remove(node);
                return node;
            }
            return null;
        }
    }

    int capacity, minFreq;
    Map<Integer, Node> keyMap;
    Map<Integer, DLList> freqMap;

    public LFUCache(int capacity) {
        this.capacity = capacity;
        minFreq = 0;
        keyMap = new HashMap<>();
        freqMap = new HashMap<>();
    }

    public int get(int key) {
        if (!keyMap.containsKey(key)) return -1;
        Node node = keyMap.get(key);
        update(node);
        return node.value;
    }

    public void put(int key, int value) {
        if (capacity == 0) return;

        if (keyMap.containsKey(key)) {
            Node node = keyMap.get(key);
            node.value = value;
            update(node);
            return;
        }

        if (keyMap.size() >= capacity) {
            DLList minList = freqMap.get(minFreq);
            Node lru = minList.removeTail();
            keyMap.remove(lru.key);
        }

        Node newNode = new Node(key, value);
        keyMap.put(key, newNode);
        minFreq = 1;
        freqMap.computeIfAbsent(1, k -> new DLList()).addHead(newNode);
    }

    private void update(Node node) {
        int freq = node.freq;
        DLList list = freqMap.get(freq);
        list.remove(node);
        
        if (freq == minFreq && list.size == 0) {
            minFreq++;
        }
        
        node.freq++;
        freqMap.computeIfAbsent(node.freq, k -> new DLList()).addHead(node);
    }
    
    public static void main(String[] args) {
         LFUCache lfu = new LFUCache(2);
         lfu.put(1, 1);
         lfu.put(2, 2);
         System.out.println("Get 1 (Expect 1): " + lfu.get(1));
         lfu.put(3, 3); // 2 is LFU (freq 1), 1 is freq 2. Evict 2.
         System.out.println("Get 2 (Expect -1): " + lfu.get(2));
         System.out.println("Get 3 (Expect 3): " + lfu.get(3));
         lfu.put(4, 4); // 1 is freq 2. 3 is freq 1. Evict 3.
         System.out.println("Get 1 (Expect 1): " + lfu.get(1)); // 1 is freq 3
         System.out.println("Get 3 (Expect -1): " + lfu.get(3));
         System.out.println("Get 4 (Expect 4): " + lfu.get(4));
    }
}
```

## 🌍 Real-World Analogy
### **Library Book Shelves:**
Think of a library with a "Popular Reads" section with limited space. 
- You track how many times each book is borrowed.
- High-frequency books stay. 
- When space is needed, you remove the book borrowed the fewest times (`minFreq`). 
- If multiple books tie for "least borrowed", you remove the one that hasn't been touched for the longest time (LRU tie-breaker).

## 🎯 Summary
✅ **Complexity Management:** By bucketing nodes into frequency lists, we avoid sorting. We just move a node from List $F$ to List $F+1$ in $O(1)$.
