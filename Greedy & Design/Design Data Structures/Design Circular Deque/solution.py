class MyCircularDeque:

    def __init__(self, k: int):
        self.k = k
        self.buffer = [0] * k
        self.count = 0
        self.front = 0
        self.rear = k - 1

    def insertFront(self, value: int) -> bool:
        if self.isFull(): return False
        self.front = (self.front - 1 + self.k) % self.k
        self.buffer[self.front] = value
        self.count += 1
        return True

    def insertLast(self, value: int) -> bool:
        if self.isFull(): return False
        self.rear = (self.rear + 1) % self.k
        self.buffer[self.rear] = value
        self.count += 1
        return True

    def deleteFront(self) -> bool:
        if self.isEmpty(): return False
        self.front = (self.front + 1) % self.k
        self.count -= 1
        return True

    def deleteLast(self) -> bool:
        if self.isEmpty(): return False
        self.rear = (self.rear - 1 + self.k) % self.k
        self.count -= 1
        return True

    def getFront(self) -> int:
        return -1 if self.isEmpty() else self.buffer[self.front]

    def getRear(self) -> int:
        return -1 if self.isEmpty() else self.buffer[self.rear]

    def isEmpty(self) -> bool:
        return self.count == 0

    def isFull(self) -> bool:
        return self.count == self.k

if __name__ == "__main__":
    deque = MyCircularDeque(3)
    print(f"Insert Last 1: {deque.insertLast(1)}")
    print(f"Insert Last 2: {deque.insertLast(2)}")
    print(f"Insert Front 3: {deque.insertFront(3)}")
    print(f"Insert Front 4 (Full): {deque.insertFront(4)}")
    print(f"Get Rear (2): {deque.getRear()}")
    print(f"Is Full (True): {deque.isFull()}")
    print(f"Delete Last: {deque.deleteLast()}")
    print(f"Get Front (3): {deque.getFront()}")
