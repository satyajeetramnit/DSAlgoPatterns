from typing import List

class Solution:
    def outerTrees(self, trees: List[List[int]]) -> List[List[int]]:
        def cross_product(o, a, b):
            return (a[0] - o[0]) * (b[1] - o[1]) - (a[1] - o[1]) * (b[0] - o[0])

        trees.sort(key=lambda x: (x[0], x[1]))
        
        lower = []
        for p in trees:
            while len(lower) >= 2 and cross_product(lower[-2], lower[-1], p) < 0:
                lower.pop()
            lower.append(tuple(p))
            
        upper = []
        for p in reversed(trees):
            while len(upper) >= 2 and cross_product(upper[-2], upper[-1], p) < 0:
                upper.pop()
            upper.append(tuple(p))
            
        return [list(p) for p in set(lower + upper)]

if __name__ == "__main__":
    sol = Solution()
    points = [[1,1],[2,2],[2,0],[2,4],[3,3],[4,2]]
    hull = sol.outerTrees(points)
    # Sort for consistent output verification
    hull.sort()
    print(f"Test Case 1 Output: {hull}")
