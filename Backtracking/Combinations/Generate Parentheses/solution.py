from typing import List

class Solution:
    def generateParenthesis(self, n: int) -> List[str]:
        res = []
        self._backtrack(n, 0, 0, [], res)
        return res

    def _backtrack(self, n, open_count, close_count, current, res):
        if len(current) == n * 2:
            res.append("".join(current))
            return
        
        if open_count < n:
            current.append("(")
            self._backtrack(n, open_count + 1, close_count, current, res)
            current.pop()
            
        if close_count < open_count:
            current.append(")")
            self._backtrack(n, open_count, close_count + 1, current, res)
            current.pop()

if __name__ == "__main__":
    sol = Solution()
    print(f"Generate Parentheses n=3: {sol.generateParenthesis(3)}")
    print(f"Generate Parentheses n=1: {sol.generateParenthesis(1)}")
