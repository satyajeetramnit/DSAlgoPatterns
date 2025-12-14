from typing import List

class Solution:
    def criticalConnections(self, n: int, connections: List[List[int]]) -> List[List[int]]:
        adj = [[] for _ in range(n)]
        for u, v in connections:
            adj[u].append(v)
            adj[v].append(u)
            
        disc = [-1] * n
        low = [-1] * n
        self.time = 0
        bridges = []
        
        def dfs(u, p):
            disc[u] = low[u] = self.time
            self.time += 1
            
            for v in adj[u]:
                if v == p:
                    continue
                
                if disc[v] != -1:
                    low[u] = min(low[u], disc[v])
                else:
                    dfs(v, u)
                    low[u] = min(low[u], low[v])
                    if low[v] > disc[u]:
                        bridges.append(sorted([u, v]))
                        
        dfs(0, -1)
        return bridges

if __name__ == "__main__":
    sol = Solution()
    
    # Test 1
    conn1 = [[0,1],[1,2],[2,0],[1,3]]
    res1 = sol.criticalConnections(4, conn1)
    # Expected: [[1,3]]
    assert len(res1) == 1
    assert res1[0] == [1, 3]
    print("Test 1 Passed")
    
    # Test 2
    conn2 = [[0,1]]
    res2 = sol.criticalConnections(2, conn2)
    assert len(res2) == 1
    assert res2[0] == [0, 1]
    print("Test 2 Passed")
