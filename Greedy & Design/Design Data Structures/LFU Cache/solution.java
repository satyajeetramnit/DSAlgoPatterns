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
         lfu.put(3, 3);
         System.out.println("Get 2 (Expect -1): " + lfu.get(2));
         System.out.println("Get 3 (Expect 3): " + lfu.get(3));
         lfu.put(4, 4);
         // 1 and 3 are both Freq 2. 1 was promoted first, so 1 is LRU. Evict 1.
         System.out.println("Get 1 (Expect -1): " + lfu.get(1));
         System.out.println("Get 3 (Expect 3): " + lfu.get(3));
         System.out.println("Get 4 (Expect 4): " + lfu.get(4));
    }
}
