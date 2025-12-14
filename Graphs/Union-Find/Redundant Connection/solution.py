from typing import List

class DSU:
    def __init__(self, n):
        self.parent = list(range(n + 1))
    
    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]
    
    def union(self, x, y):
        rootX = self.find(x)
        rootY = self.find(y)
        if rootX != rootY:
            self.parent[rootX] = rootY
            return True
        return False

class Solution:
    def findRedundantConnection(self, edges: List[List[int]]) -> List[int]:
        n = len(edges)
        dsu = DSU(n)
        
        for u, v in edges:
            if not dsu.union(u, v):
                return [u, v]
                
        return []

if __name__ == "__main__":
    sol = Solution()
    print(f"Redundant 1: {sol.findRedundantConnection([[1,2], [1,3], [2,3]])}")
    print(f"Redundant 2: {sol.findRedundantConnection([[1,2], [2,3], [3,4], [1,4], [1,5]])}")
