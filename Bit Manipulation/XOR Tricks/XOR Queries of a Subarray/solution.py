from typing import List

class Solution:
    def xorQueries(self, arr: List[int], queries: List[List[int]]) -> List[int]:
        # Copy to avoid modifying input if that matters, but problem says we can use array
        nums = list(arr)
        for i in range(1, len(nums)):
            nums[i] ^= nums[i-1]
            
        res = []
        for l, r in queries:
            if l > 0:
                res.append(nums[r] ^ nums[l-1])
            else:
                res.append(nums[r])
        return res

if __name__ == "__main__":
    sol = Solution()
    print(f"Test Case 1: {sol.xorQueries([1,3,4,8], [[0,1],[1,2],[0,3],[3,3]])}") # [2, 7, 14, 8]
    print(f"Test Case 2: {sol.xorQueries([4,8,2,10], [[2,3],[1,3],[0,0],[0,3]])}") # [8, 0, 4, 4]
