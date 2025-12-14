from typing import List

class DSU:
    def __init__(self, n):
        self.parent = list(range(n))
        self.count = n
        
    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]
        
    def union(self, x, y):
        rootX = self.find(x)
        rootY = self.find(y)
        if rootX != rootY:
            self.parent[rootX] = rootY
            self.count -= 1

class Solution:
    def findCircleNum(self, isConnected: List[List[int]]) -> int:
        n = len(isConnected)
        dsu = DSU(n)
        
        for i in range(n):
            for j in range(i + 1, n):
                if isConnected[i][j] == 1:
                    dsu.union(i, j)
                    
        return dsu.count

if __name__ == "__main__":
    sol = Solution()
    print(f"Provinces 1: {sol.findCircleNum([[1,1,0],[1,1,0],[0,0,1]])}")
    print(f"Provinces 2: {sol.findCircleNum([[1,0,0],[0,1,0],[0,0,1]])}")
