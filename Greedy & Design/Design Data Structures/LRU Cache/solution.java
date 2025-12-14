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

    public static void main(String[] args) {
        LRUCache lRUCache = new LRUCache(2);
        lRUCache.put(1, 1);
        lRUCache.put(2, 2);
        System.out.println("Get 1 (Expect 1): " + lRUCache.get(1));
        lRUCache.put(3, 3);
        System.out.println("Get 2 (Expect -1): " + lRUCache.get(2));
        lRUCache.put(4, 4);
        System.out.println("Get 1 (Expect -1): " + lRUCache.get(1));
        System.out.println("Get 3 (Expect 3): " + lRUCache.get(3));
        System.out.println("Get 4 (Expect 4): " + lRUCache.get(4));
    }
}
