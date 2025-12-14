from typing import List

class Solution:
    def mctFromLeafValues(self, arr: List[int]) -> int:
        res = 0
        stack = [float('inf')]
        
        for num in arr:
            while stack[-1] <= num:
                mid = stack.pop()
                res += mid * min(stack[-1], num)
            stack.append(num)
            
        while len(stack) > 2:
            mid = stack.pop()
            res += mid * stack[-1]
            
        return res

if __name__ == "__main__":
    sol = Solution()
    print(f"Test Case 1: {sol.mctFromLeafValues([6,2,4])}") # 32
    print(f"Test Case 2: {sol.mctFromLeafValues([4,11])}") # 44
