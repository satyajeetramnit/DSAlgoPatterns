class Solution:
    def characterReplacement(self, s: str, k: int) -> int:
        count = {}
        left = 0
        max_freq = 0
        max_len = 0
        
        for right in range(len(s)):
            char = s[right]
            count[char] = count.get(char, 0) + 1
            max_freq = max(max_freq, count[char])
            
            if (right - left + 1) - max_freq > k:
                count[s[left]] -= 1
                left += 1
            
            max_len = max(max_len, right - left + 1)
            
        return max_len

if __name__ == "__main__":
    sol = Solution()
    s1 = "ABAB"
    k1 = 2
    print(f"Max Length 1: {sol.characterReplacement(s1, k1)}") # Expected: 4

    s2 = "AABABBA"
    k2 = 1
    print(f"Max Length 2: {sol.characterReplacement(s2, k2)}") # Expected: 4
