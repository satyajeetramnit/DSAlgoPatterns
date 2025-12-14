from typing import List

class Solution:
    def maxProduct(self, words: List[str]) -> int:
        n = len(words)
        masks = [0] * n
        lens = [0] * n
        
        for i, w in enumerate(words):
            lens[i] = len(w)
            for char in w:
                masks[i] |= (1 << (ord(char) - ord('a')))
                
        max_prod = 0
        for i in range(n):
            for j in range(i + 1, n):
                if (masks[i] & masks[j]) == 0:
                    max_prod = max(max_prod, lens[i] * lens[j])
                    
        return max_prod

if __name__ == "__main__":
    sol = Solution()
    print(f"Test Case 1: {sol.maxProduct(['abcw','baz','foo','bar','xtfn','abcdef'])}") # 16
    print(f"Test Case 2: {sol.maxProduct(['a','ab','abc','d','cd','bcd','abcd'])}") # 4
    print(f"Test Case 3: {sol.maxProduct(['a','aa','aaa','aaaa'])}") # 0
