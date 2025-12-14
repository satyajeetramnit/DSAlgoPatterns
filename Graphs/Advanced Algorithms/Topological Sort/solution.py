from typing import List
from collections import deque, defaultdict

class Solution:
    def findOrder(self, numCourses: int, prerequisites: List[List[int]]) -> List[int]:
        adj = defaultdict(list)
        in_degree = [0] * numCourses
        
        for dest, src in prerequisites:
            adj[src].append(dest)
            in_degree[dest] += 1
            
        q = deque([i for i in range(numCourses) if in_degree[i] == 0])
        order = []
        
        while q:
            u = q.popleft()
            order.append(u)
            
            for v in adj[u]:
                in_degree[v] -= 1
                if in_degree[v] == 0:
                    q.append(v)
                    
        return order if len(order) == numCourses else []

if __name__ == "__main__":
    sol = Solution()
    
    print(f"Order 1: {sol.findOrder(2, [[1,0]])}")
    print(f"Order 2: {sol.findOrder(4, [[1,0],[2,0],[3,1],[3,2]])}")
    print(f"Order 3: {sol.findOrder(2, [[1,0],[0,1]])}")
