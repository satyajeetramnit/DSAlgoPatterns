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
                # popitem(last=False) removes Front (FIFO).
                # Since we add new items to the end?
                # Wait. Default dict doesn't mean ordered.
                # But OrderedDict does.
                # Where do we add? 
                # self.freq_map[node.freq][node.key] = node adds to END.
                # So END is MRU.
                # So Front is LRU.
                # popitem(last=False) is correct.
                k, _ = self.freq_map[self.min_freq].popitem(last=False)
                del self.key_map[k]
                if not self.freq_map[self.min_freq]:
                    del self.freq_map[self.min_freq]
            
            # Insert new
            self.min_freq = 1
            node = Node(key, value)
            self.key_map[key] = node
            self.freq_map[1][key] = node

if __name__ == "__main__":
    lfu = LFUCache(2)
    lfu.put(1, 1)
    lfu.put(2, 2)
    print(f"Get 1 (Expect 1): {lfu.get(1)}")
    lfu.put(3, 3) 
    print(f"Get 2 (Expect -1): {lfu.get(2)}")
    print(f"Get 3 (Expect 3): {lfu.get(3)}")
    lfu.put(4, 4)
    # 1 and 3 are both Freq 2. 1 was promoted first, so 1 is LRU. Evict 1.
    print(f"Get 1 (Expect -1): {lfu.get(1)}")
    print(f"Get 3 (Expect 3): {lfu.get(3)}")
    print(f"Get 4 (Expect 4): {lfu.get(4)}")
