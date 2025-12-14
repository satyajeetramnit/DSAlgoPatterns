import heapq
from typing import List
import collections

class Solution:
    def medianSlidingWindow(self, nums: List[int], k: int) -> List[float]:
        small, large = [], [] # Max heap (neg), Min heap
        mapper = collections.defaultdict(int)
        result = []
        
        # Init first k
        for i, num in enumerate(nums[:k]):
            heapq.heappush(small, -num)
            heapq.heappush(large, -heapq.heappop(small))
            if len(large) > len(small):
                heapq.heappush(small, -heapq.heappop(large))
                
        for i in range(k, len(nums) + 1):
            median = -small[0] if k % 2 == 1 else (-small[0] + large[0]) / 2.0
            result.append(float(median))
            
            if i == len(nums): break
            
            out_num = nums[i-k]
            in_num = nums[i]
            balance = 0 
            
            # Decide where out_num is leaving from
            if out_num <= -small[0]:
                balance -= 1
                if out_num == -small[0]: 
                    heapq.heappop(small)
                else: 
                    mapper[out_num] += 1
            else:
                balance += 1
                if out_num == large[0]: 
                    heapq.heappop(large)
                else: 
                    mapper[out_num] += 1
                
            # Add in_num
            if small and in_num <= -small[0]:
                heapq.heappush(small, -in_num)
                balance += 1
            else:
                heapq.heappush(large, in_num)
                balance -= 1
                
            # Rebalance
            if balance < 0: # Small needs one
                heapq.heappush(small, -heapq.heappop(large)) 
            elif balance > 0: # Large needs one
                heapq.heappush(large, -heapq.heappop(small))
            
            # Clean tops
            while small and mapper[-small[0]] > 0:
                mapper[-small[0]] -= 1
                heapq.heappop(small)
            while large and mapper[large[0]] > 0:
                mapper[large[0]] -= 1
                heapq.heappop(large)
                
        return result

if __name__ == "__main__":
    sol = Solution()
    nums = [1,3,-1,-3,5,3,6,7]
    k = 3
    print(f"Test Case 1: {sol.medianSlidingWindow(nums, k)}") # Expect [1.0, -1.0, -1.0, 3.0, 5.0, 6.0]
