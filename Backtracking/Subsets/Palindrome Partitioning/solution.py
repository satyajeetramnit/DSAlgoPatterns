from typing import List

class Solution:
    def partition(self, s: str) -> List[List[str]]:
        res = []
        self._backtrack(s, 0, [], res)
        return res

    def _backtrack(self, s, start, path, res):
        if start == len(s):
            res.append(path[:])
            return
            
        for i in range(start, len(s)):
            if self._isPalindrome(s, start, i):
                path.append(s[start:i+1])
                self._backtrack(s, i + 1, path, res)
                path.pop()

    def _isPalindrome(self, s, left, right):
        while left < right:
            if s[left] != s[right]:
                return False
            left += 1
            right -= 1
        return True

if __name__ == "__main__":
    sol = Solution()
    print(f"Partition 'aab': {sol.partition('aab')}")
