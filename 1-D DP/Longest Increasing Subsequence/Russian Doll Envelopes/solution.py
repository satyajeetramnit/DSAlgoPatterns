from typing import List
import bisect

class Solution:
    def maxEnvelopes(self, envelopes: List[List[int]]) -> int:
        # Sort: width ascending, height descending
        # In Python, we can sort by (w, -h)
        envelopes.sort(key=lambda x: (x[0], -x[1]))
        
        tails = []
        for _, h in envelopes:
            idx = bisect.bisect_left(tails, h)
            if idx < len(tails):
                tails[idx] = h
            else:
                tails.append(h)
        return len(tails)

if __name__ == "__main__":
    sol = Solution()
    
    env1 = [[5,4],[6,4],[6,7],[2,3]]
    print(f"Test Case 1: {sol.maxEnvelopes(env1)}") # 3
    
    env2 = [[1,1],[1,1],[1,1]]
    print(f"Test Case 2: {sol.maxEnvelopes(env2)}") # 1
