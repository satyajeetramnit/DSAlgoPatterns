class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        char_set = set()
        left = 0
        max_length = 0
        
        for right in range(len(s)):
            while s[right] in char_set:
                char_set.remove(s[left])
                left += 1
            char_set.add(s[right])
            max_length = max(max_length, right - left + 1)
            
        return max_length

if __name__ == "__main__":
    sol = Solution()
    s1 = "abcabcbb"
    print(f"Length 1: {sol.lengthOfLongestSubstring(s1)}") # Expected: 3

    s2 = "bbbbb"
    print(f"Length 2: {sol.lengthOfLongestSubstring(s2)}") # Expected: 1
    
    s3 = "pwwkew"
    print(f"Length 3: {sol.lengthOfLongestSubstring(s3)}") # Expected: 3
