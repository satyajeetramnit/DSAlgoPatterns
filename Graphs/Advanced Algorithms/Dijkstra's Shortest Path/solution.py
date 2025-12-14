import heapq
from typing import List, Tuple

class Solution:
    def dijkstra(self, V: int, adj: List[List[Tuple[int, int]]], S: int) -> List[int]:
        pq = [(0, S)]
        dist = [float('inf')] * V
        dist[S] = 0
        
        while pq:
            d, u = heapq.heappop(pq)
            
            if d > dist[u]:
                continue
            
            for v, w in adj[u]:
                if dist[u] + w < dist[v]:
                    dist[v] = dist[u] + w
                    heapq.heappush(pq, (dist[v], v))
        
        # Convert INF to -1 for easier printing/testing if unreachable
        return [d if d != float('inf') else -1 for d in dist]

if __name__ == "__main__":
    sol = Solution()
    V = 3
    S = 2
    # adj is list of lists. adj[u] = [(v, w)]
    adj = [[] for _ in range(V)]
    adj[2].append((1, 1))
    adj[2].append((0, 6))
    adj[1].append((0, 3))
    
    print(f"Distances: {sol.dijkstra(V, adj, S)}")
