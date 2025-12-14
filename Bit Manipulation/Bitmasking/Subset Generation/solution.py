from typing import List

class Solution:
    def subsets(self, nums: List[int]) -> List[List[int]]:
        n = len(nums)
        total_subsets = 1 << n
        res = []
        
        for mask in range(total_subsets):
            subset = []
            for i in range(n):
                if (mask >> i) & 1:
                    subset.append(nums[i])
            res.append(subset)
            
        return res

if __name__ == "__main__":
    sol = Solution()
    res = sol.subsets([1,2,3])
    print(f"Test Case 1 (Size should be 8): {len(res)}")
    print(res)
