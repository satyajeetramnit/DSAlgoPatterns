import heapq
from typing import List

class KthLargest:

    def __init__(self, k: int, nums: List[int]):
        self.k = k
        self.heap = []
        for num in nums:
            self.add(num) # Re-use logic to ensure heap size constraint

    def add(self, val: int) -> int:
        heapq.heappush(self.heap, val)
        if len(self.heap) > self.k:
            heapq.heappop(self.heap)
        return self.heap[0]

if __name__ == "__main__":
    kthLargest = KthLargest(3, [4, 5, 8, 2])
    print("Test Case 1:")
    print(f"Add 3: {kthLargest.add(3)}")   # 4
    print(f"Add 5: {kthLargest.add(5)}")   # 5
    print(f"Add 10: {kthLargest.add(10)}") # 5
    print(f"Add 9: {kthLargest.add(9)}")   # 8
    print(f"Add 4: {kthLargest.add(4)}")   # 8
