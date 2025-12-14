from typing import List

class Solution:
    def findRepeatedDnaSequences(self, s: str) -> List[str]:
        seen, repeated = set(), set()
        
        for i in range(len(s) - 9):
            sub = s[i : i+10]
            if sub in seen:
                repeated.add(sub)
            else:
                seen.add(sub)
                
        return list(repeated)

if __name__ == "__main__":
    sol = Solution()
    s1 = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
    res1 = sol.findRepeatedDnaSequences(s1)
    print(f"Repeated 1: {res1}") # Expected: ["AAAAACCCCC", "CCCCCAAAAA"] (order varies)

    s2 = "AAAAAAAAAAAAA"
    res2 = sol.findRepeatedDnaSequences(s2)
    print(f"Repeated 2: {res2}") # Expected: ["AAAAAAAAAA"]
