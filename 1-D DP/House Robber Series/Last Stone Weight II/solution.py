from typing import List

class Solution:
    def lastStoneWeightII(self, stones: List[int]) -> int:
        total_sum = sum(stones)
        target = total_sum // 2
        
        dp = {0}
        
        for stone in stones:
            new_sums = set()
            for s in dp:
                if s + stone <= target:
                    new_sums.add(s + stone)
            dp.update(new_sums)
            
        max_s1 = max(dp)
        return total_sum - 2 * max_s1

if __name__ == "__main__":
    sol = Solution()
    
    print(f"Test Case 1: {sol.lastStoneWeightII([2,7,4,1,8,1])}") # 1
    print(f"Test Case 2: {sol.lastStoneWeightII([31,26,33,21,40])}") # 5
