from typing import List

class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        res = []
        self._backtrack(nums, [], [False]*len(nums), res)
        return res

    def _backtrack(self, nums, path, used, res):
        if len(path) == len(nums):
            res.append(path[:])
            return

        for i in range(len(nums)):
            if used[i]:
                continue
            
            used[i] = True
            path.append(nums[i])
            self._backtrack(nums, path, used, res)
            path.pop()
            used[i] = False

    def permuteUnique(self, nums: List[int]) -> List[List[int]]:
        nums.sort() # Key for handling duplicates
        res = []
        self._backtrackUnique(nums, [], [False]*len(nums), res)
        return res

    def _backtrackUnique(self, nums, path, used, res):
        if len(path) == len(nums):
            res.append(path[:])
            return

        for i in range(len(nums)):
            if used[i]:
                continue
            # If current is same as prev and prev not used, skip
            if i > 0 and nums[i] == nums[i-1] and not used[i-1]:
                continue
                
            used[i] = True
            path.append(nums[i])
            self._backtrackUnique(nums, path, used, res)
            path.pop()
            used[i] = False

if __name__ == "__main__":
    sol = Solution()
    
    nums1 = [1, 2, 3]
    res1 = sol.permute(nums1)
    print(f"Permute [1,2,3]: {res1}")

    nums2 = [1, 1, 2]
    res2 = sol.permuteUnique(nums2)
    print(f"PermuteUnique [1,1,2]: {res2}")
