from typing import List

class Solution:
    def robLinear(self, nums: List[int]) -> int:
        prev1, prev2 = 0, 0
        for num in nums:
            current = max(prev1, prev2 + num)
            prev2 = prev1
            prev1 = current
        return prev1

    def rob1(self, nums: List[int]) -> int:
        return self.robLinear(nums)

    def rob2(self, nums: List[int]) -> int:
        n = len(nums)
        if n == 0: return 0
        if n == 1: return nums[0]
        return max(self.robLinear(nums[:-1]), self.robLinear(nums[1:]))

if __name__ == "__main__":
    sol = Solution()
    
    print(f"Robber I - Test 1: {sol.rob1([1, 2, 3, 1])}") # 4
    print(f"Robber I - Test 2: {sol.rob1([2, 7, 9, 3, 1])}") # 12
    
    print(f"Robber II - Test 3: {sol.rob2([2, 3, 2])}") # 3
    print(f"Robber II - Test 4: {sol.rob2([1, 2, 3, 1])}") # 4
