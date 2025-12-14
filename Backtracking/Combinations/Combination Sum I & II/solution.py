from typing import List

class Solution:
    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        res = []
        self._dfs1(candidates, target, 0, [], res)
        return res

    def _dfs1(self, candidates, target, start, path, res):
        if target == 0:
            res.append(path[:])
            return
        if target < 0:
            return
            
        for i in range(start, len(candidates)):
            path.append(candidates[i])
            self._dfs1(candidates, target - candidates[i], i, path, res)
            path.pop()

    def combinationSum2(self, candidates: List[int], target: int) -> List[List[int]]:
        candidates.sort()
        res = []
        self._dfs2(candidates, target, 0, [], res)
        return res

    def _dfs2(self, candidates, target, start, path, res):
        if target == 0:
            res.append(path[:])
            return
        if target < 0:
            return
        
        for i in range(start, len(candidates)):
            if i > start and candidates[i] == candidates[i-1]:
                continue
            path.append(candidates[i])
            self._dfs2(candidates, target - candidates[i], i + 1, path, res)
            path.pop()

if __name__ == "__main__":
    sol = Solution()
    
    c1 = [2,3,6,7]
    t1 = 7
    print(f"Combination Sum I [2,3,6,7] t=7: {sol.combinationSum(c1, t1)}")
    
    c2 = [10,1,2,7,6,1,5]
    t2 = 8
    print(f"Combination Sum II [10,1,2,7,6,1,5] t=8: {sol.combinationSum2(c2, t2)}")
