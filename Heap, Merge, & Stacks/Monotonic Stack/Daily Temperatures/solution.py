from typing import List

class Solution:
    def dailyTemperatures(self, temperatures: List[int]) -> List[int]:
        n = len(temperatures)
        answer = [0] * n
        stack = [] # stores indices
        
        for i, temp in enumerate(temperatures):
            while stack and temp > temperatures[stack[-1]]:
                idx = stack.pop()
                answer[idx] = i - idx
            stack.append(i)
            
        return answer

if __name__ == "__main__":
    sol = Solution()
    temps = [73,74,75,71,69,72,76,73]
    print(f"Test Case 1: {sol.dailyTemperatures(temps)}") # Expect [1, 1, 4, 2, 1, 1, 0, 0]
