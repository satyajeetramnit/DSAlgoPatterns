# LRU Cache

## 🧩 Problem Statement
Design a data structure that follows the constraints of a **Least Recently Used (LRU) cache**.

Implement the `LRUCache` class:
- `LRUCache(int capacity)` Initialize the LRU cache with positive size `capacity`.
- `int get(int key)` Return the value of the `key` if the key exists, otherwise return `-1`.
- `void put(int key, int value)` Update the value of the `key` if the `key` exists. Otherwise, add the `key-value` pair to the cache. If the number of keys exceeds the `capacity` from this operation, **evict** the least recently used key.

The functions `get` and `put` must each run in $O(1)$ average time complexity.

## 🔍 Approaches

### 1. Hash Map + Doubly Linked List ($O(1)$)
- **Concept:** We need $O(1)$ access (Hash Map) and $O(1)$ removal/insertion at both ends to maintain order (Doubly Linked List).
- **Structure:**
  - **Map:** `key -> Node*` (points to the node in the list).
  - **List:** Stores nodes ordered by access time.
    - **Head:** Most Recently Used (MRU).
    - **Tail:** Least Recently Used (LRU).
- **Operations:**
  - `get(key)`: If in map, move the node to the **Head**. Return value.
  - `put(key, value)`:
    - If exists: Update value, move to **Head**.
    - If new: Create node, add to **Head**, add to Map.
    - If capacity exceeded: Remove **Tail** node, remove from Map.

### 🏛️ Design Diagram
```mermaid
graph TD
    subgraph HashMap
    k1[Key: 1] -->|Ptr| n1
    k2[Key: 2] -->|Ptr| n2
    k3[Key: 3] -->|Ptr| n3
    end

    subgraph DoublyLinkedList
    direction LR
    Head((Head)) <--> n3[Node 3 (MRU)] <--> n1[Node 1] <--> n2[Node 2 (LRU)] <--> Tail((Tail))
    end
    
    style Head fill:#4caf50,stroke:#333,stroke-width:2px
    style Tail fill:#f44336,stroke:#333,stroke-width:2px
    style n3 fill:#2196f3,stroke:#333,stroke-width:2px
```

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(1)$ for both `get` and `put`.
- **Space Complexity:** $O(C)$ where $C$ is capacity.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <unordered_map>
#include <list>
#include <iostream>

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
```

### Python
```python
class Node:
    def __init__(self, key, val):
        self.key = key
        self.val = val
        self.prev = None
        self.next = None

class LRUCache:
    def __init__(self, capacity: int):
        self.capacity = capacity
        self.cache = {} # key -> Node
        # Dummy head (MRU) and tail (LRU)
        self.head = Node(0, 0)
        self.tail = Node(0, 0)
        self.head.next = self.tail
        self.tail.prev = self.head

    def _remove(self, node):
        prev, nxt = node.prev, node.next
        prev.next = nxt
        nxt.prev = prev

    def _add_to_front(self, node):
        # Insert after head
        nxt = self.head.next
        self.head.next = node
        node.prev = self.head
        node.next = nxt
        nxt.prev = node

    def get(self, key: int) -> int:
        if key in self.cache:
            node = self.cache[key]
            self._remove(node)
            self._add_to_front(node)
            return node.val
        return -1

    def put(self, key: int, value: int) -> None:
        if key in self.cache:
            self._remove(self.cache[key])
        
        node = Node(key, value)
        self._add_to_front(node)
        self.cache[key] = node
        
        if len(self.cache) > self.capacity:
            # Remove LRU (node before tail)
            lru = self.tail.prev
            self._remove(lru)
            del self.cache[lru.key]
```

### Java
```java
import java.util.HashMap;
import java.util.Map;

class LRUCache {
    class Node {
        int key;
        int value;
        Node prev;
        Node next;
        Node(int key, int value) {
            this.key = key;
            this.value = value;
        }
    }

    private Map<Integer, Node> cache;
    private int capacity;
    private Node head, tail;

    public LRUCache(int capacity) {
        this.capacity = capacity;
        cache = new HashMap<>();
        head = new Node(0, 0); // Dummy MRU
        tail = new Node(0, 0); // Dummy LRU
        head.next = tail;
        tail.prev = head;
    }

    private void remove(Node node) {
        node.prev.next = node.next;
        node.next.prev = node.prev;
    }

    private void addToFront(Node node) {
        node.next = head.next;
        node.prev = head;
        head.next.prev = node;
        head.next = node;
    }

    public int get(int key) {
        if (cache.containsKey(key)) {
            Node node = cache.get(key);
            remove(node);
            addToFront(node);
            return node.value;
        }
        return -1;
    }

    public void put(int key, int value) {
        if (cache.containsKey(key)) {
            Node node = cache.get(key);
            node.value = value;
            remove(node);
            addToFront(node);
        } else {
            Node newNode = new Node(key, value);
            cache.put(key, newNode);
            addToFront(newNode);
            if (cache.size() > capacity) {
                Node lru = tail.prev;
                remove(lru);
                cache.remove(lru.key);
            }
        }
    }
}
```

### 🏛️ Visual Logic: The "Recency" Chain

List: `[A] <-> [B] <-> [C]`. (A is LRU, C is MRU).

1. **Get(A)**:
   - A is accessed. It must become MRU.
   - Detach A: `[B] <-> [C]`.
   - Attach A to Front: `[B] <-> [C] <-> [A]`.
   - List State: `B` is now LRU.

2. **Put(D)** (Capacity Full):
   - Capacity 3. Size is 3.
   - Evict LRU (`B`).
   - Detach B: `[C] <-> [A]`.
   - Create D, Attach to Front: `[C] <-> [A] <-> [D]`.
   - Map: Remove B, Add D.

## 🌍 Real-World Analogy
### **Netflix "Continue Watching" Row:**
Your "Continue Watching" list on Netflix has limited slots.
- **Access (Get/Put)**: When you play a movie, it pops to the **front** (leftmost) of the list.
- **Eviction**: If you start a new movie and the row is full, the movie you watched **longest ago** (at the far right) falls off the list to make space.

### **Phone Background Apps:**
Your phone keeps recent apps in memory. When you switch to an app, it becomes the "Most Recently Used" and stays in memory. If you open too many apps, the OS kills the one you haven't used for the longest time ("Least Recently Used") to free up RAM.

## 🎯 Summary
✅ **Combination:** Combining a Hash Map (speed) with a Linked List (order) allows us to satisfy the $O(1)$ constraint for both lookup and ordering updates.
