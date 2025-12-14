class Solution:
    def checkInclusion(self, s1: str, s2: str) -> bool:
        if len(s1) > len(s2):
            return False
        
        s1_count = [0] * 26
        s2_count = [0] * 26
        
        # Initialize
        for i in range(len(s1)):
            s1_count[ord(s1[i]) - ord('a')] += 1
            s2_count[ord(s2[i]) - ord('a')] += 1
            
        if s1_count == s2_count:
            return True
            
        # Slide
        for i in range(len(s1), len(s2)):
            s2_count[ord(s2[i]) - ord('a')] += 1
            s2_count[ord(s2[i - len(s1)]) - ord('a')] -= 1
            
            if s1_count == s2_count:
                return True
                
        return False

if __name__ == "__main__":
    sol = Solution()
    s1 = "ab"
    s2 = "eidbaooo"
    print(f"Contains Permutation 1: {sol.checkInclusion(s1, s2)}") # Expected: True

    s1 = "ab"
    s2 = "eidboaoo"
    print(f"Contains Permutation 2: {sol.checkInclusion(s1, s2)}") # Expected: False
