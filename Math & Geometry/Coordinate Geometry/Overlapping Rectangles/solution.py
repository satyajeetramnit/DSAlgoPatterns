from typing import List

class Solution:
    def isRectangleOverlap(self, rec1: List[int], rec2: List[int]) -> bool:
        # Check if ranges overlap strictly
        # x-overlap: max(x1, x1') < min(x2, x2')
        # y-overlap: max(y1, y1') < min(y2, y2')
        return (max(rec1[0], rec2[0]) < min(rec1[2], rec2[2]) and
                max(rec1[1], rec2[1]) < min(rec1[3], rec2[3]))

if __name__ == "__main__":
    sol = Solution()
    print(f"Test Case 1 (Overlap): {sol.isRectangleOverlap([0,0,2,2], [1,1,3,3])}") # True
    print(f"Test Case 2 (Touch): {sol.isRectangleOverlap([0,0,1,1], [1,0,2,1])}") # False
