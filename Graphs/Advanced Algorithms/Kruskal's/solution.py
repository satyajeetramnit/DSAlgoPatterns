from typing import List

class DSU:
    def __init__(self, n):
        self.parent = list(range(n))
    
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
    def minSpanningTree(self, V: int, edges: List[List[int]]) -> int:
        # edges: [u, v, w]
        edges.sort(key=lambda x: x[2])
        
        dsu = DSU(V)
        mst_weight = 0
        
        for u, v, w in edges:
            if dsu.union(u, v):
                mst_weight += w
                
        return mst_weight

if __name__ == "__main__":
    sol = Solution()
    print(f"MST 1: {sol.minSpanningTree(3, [[0,1,5], [1,2,3], [0,2,1]])}")
    print(f"MST 2: {sol.minSpanningTree(2, [[0,1,5]])}")
