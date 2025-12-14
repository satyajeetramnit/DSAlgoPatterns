from typing import List

class Solution:
    def subsets(self, nums: List[int]) -> List[List[int]]:
        res = []
        self._backtrack(nums, 0, [], res)
        return res

    def _backtrack(self, nums, start, path, res):
        res.append(path[:])
        
        for i in range(start, len(nums)):
            path.append(nums[i])
            self._backtrack(nums, i + 1, path, res)
            path.pop()

    def subsetsWithDup(self, nums: List[int]) -> List[List[int]]:
        nums.sort()
        res = []
        self._backtrackWithDup(nums, 0, [], res)
        return res

    def _backtrackWithDup(self, nums, start, path, res):
        res.append(path[:])
        
        for i in range(start, len(nums)):
            if i > start and nums[i] == nums[i-1]:
                continue
            path.append(nums[i])
            self._backtrackWithDup(nums, i + 1, path, res)
            path.pop()

if __name__ == "__main__":
    sol = Solution()
    print(f"Subsets [1,2,3]: {sol.subsets([1,2,3])}")
    print(f"SubsetsWithDup [1,2,2]: {sol.subsetsWithDup([1,2,2])}")
