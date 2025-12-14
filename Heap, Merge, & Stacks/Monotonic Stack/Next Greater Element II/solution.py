from typing import List

class Solution:
    def nextGreaterElements(self, nums: List[int]) -> List[int]:
        n = len(nums)
        res = [-1] * n
        stack = [] # stores indices
        
        for i in range(2 * n):
            idx = i % n
            while stack and nums[idx] > nums[stack[-1]]:
                res[stack.pop()] = nums[idx]
            if i < n:
                stack.append(idx)
                
        return res

if __name__ == "__main__":
    sol = Solution()
    nums = [1, 2, 1]
    print(f"Test Case 1: {sol.nextGreaterElements(nums)}") # Expect [2, -1, 2]
