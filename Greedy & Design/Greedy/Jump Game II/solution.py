from typing import List

class Solution:
    def jump(self, nums: List[int]) -> int:
        if len(nums) <= 1:
            return 0
            
        jumps = 0
        current_end = 0
        farthest = 0
        
        for i in range(len(nums) - 1):
            farthest = max(farthest, i + nums[i])
            
            if i == current_end:
                jumps += 1
                current_end = farthest
                
                if current_end >= len(nums) - 1:
                    break
                    
        return jumps

if __name__ == "__main__":
    sol = Solution()
    print(f"Test Case 1: {sol.jump([2,3,1,1,4])}") # Expect 2
    print(f"Test Case 2: {sol.jump([2,3,0,1,4])}") # Expect 2
