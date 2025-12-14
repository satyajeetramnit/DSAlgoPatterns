from typing import List

class Solution:
    def largestRectangleArea(self, heights: List[int]) -> int:
        heights.append(0) # Dummy bar
        stack = [] # indices
        max_area = 0
        
        for i, h in enumerate(heights):
            while stack and h < heights[stack[-1]]:
                height = heights[stack.pop()]
                width = i if not stack else i - stack[-1] - 1
                max_area = max(max_area, height * width)
            stack.append(i)
            
        return max_area

if __name__ == "__main__":
    sol = Solution()
    heights = [2, 1, 5, 6, 2, 3]
    print(f"Test Case 1: {sol.largestRectangleArea(heights)}") # Expect 10
