import heapq

class MedianFinder:

    def __init__(self):
        self.small = [] # Max heap (negated)
        self.large = [] # Min heap

    def addNum(self, num: int) -> None:
        heapq.heappush(self.small, -num)
        
        # Move max of small to large
        val = -heapq.heappop(self.small)
        heapq.heappush(self.large, val)
        
        # Balance: small size must be >= large size
        if len(self.small) < len(self.large):
            val = heapq.heappop(self.large)
            heapq.heappush(self.small, -val)

    def findMedian(self) -> float:
        if len(self.small) > len(self.large):
            return float(-self.small[0])
        else:
            return (-self.small[0] + self.large[0]) / 2.0

if __name__ == "__main__":
    obj = MedianFinder()
    obj.addNum(1)
    obj.addNum(2)
    print(f"Median (1,2): {obj.findMedian()}") # 1.5
    obj.addNum(3)
    print(f"Median (1,2,3): {obj.findMedian()}") # 2.0
