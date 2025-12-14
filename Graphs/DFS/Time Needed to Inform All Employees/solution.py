from typing import List
from collections import defaultdict

class Solution:
    def numOfMinutes(self, n: int, headID: int, manager: List[int], informTime: List[int]) -> int:
        adj = defaultdict(list)
        for i, mgr in enumerate(manager):
            if mgr != -1:
                adj[mgr].append(i)
                
        def dfs(u):
            max_sub_time = 0
            for v in adj[u]:
                max_sub_time = max(max_sub_time, dfs(v))
            return informTime[u] + max_sub_time
            
        return dfs(headID)

if __name__ == "__main__":
    sol = Solution()
    
    print(f"Time 1: {sol.numOfMinutes(6, 2, [2,2,-1,2,2,2], [0,0,1,0,0,0])}")
    print(f"Time 2: {sol.numOfMinutes(7, 6, [1,2,3,4,5,6,-1], [0,6,5,4,3,2,1])}")
