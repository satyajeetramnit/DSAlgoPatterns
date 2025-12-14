import heapq
from collections import Counter, deque
from typing import List

class Solution:
    def leastInterval(self, tasks: List[str], n: int) -> int:
        count = Counter(tasks)
        max_heap = [-cnt for cnt in count.values()]
        heapq.heapify(max_heap)
        
        time = 0
        q = deque() # pairs of [-freq, idle_until_time]
        
        while max_heap or q:
            time += 1
            if max_heap:
                cnt = 1 + heapq.heappop(max_heap) # cnt is negative
                if cnt != 0:
                    q.append((cnt, time + n))
            
            if q and q[0][1] == time:
                heapq.heappush(max_heap, q.popleft()[0])
                
        return time

if __name__ == "__main__":
    sol = Solution()
    tasks = ["A","A","A","B","B","B"]
    n = 2
    print(f"Test Case 1: {sol.leastInterval(tasks, n)}") # Expect 8
