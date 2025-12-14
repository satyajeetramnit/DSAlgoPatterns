from typing import List

class Solution:
    def bagOfTokensScore(self, tokens: List[int], power: int) -> int:
        tokens.sort()
        left, right = 0, len(tokens) - 1
        score = 0
        max_score = 0
        
        while left <= right:
            if power >= tokens[left]:
                power -= tokens[left]
                score += 1
                left += 1
                max_score = max(max_score, score)
            elif score > 0:
                if left == right:
                    break
                power += tokens[right]
                score -= 1
                right -= 1
            else:
                break
                
        return max_score

if __name__ == "__main__":
    sol = Solution()
    print(f"Test Case 1: {sol.bagOfTokensScore([100], 50)}") # Expect 0
    print(f"Test Case 2: {sol.bagOfTokensScore([100, 200], 150)}") # Expect 1
    print(f"Test Case 3: {sol.bagOfTokensScore([100, 200, 300, 400], 200)}") # Expect 2
