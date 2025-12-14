from typing import List

class Solution:
    def getSubarrayBeauty(self, nums: List[int], k: int, x: int) -> List[int]:
        count = [0] * 101 # -50 to 50
        res = []
        
        def find_xth():
            current_count = 0
            # Iterate -50 to -1
            for val in range(-50, 0):
                current_count += count[val + 50]
                if current_count >= x:
                    return val
            return 0

        # Init first window
        for i in range(k):
            count[nums[i] + 50] += 1
            
        res.append(find_xth())
        
        # Slide
        for i in range(k, len(nums)):
            count[nums[i] + 50] += 1
            count[nums[i - k] + 50] -= 1
            res.append(find_xth())
            
        return res

if __name__ == "__main__":
    sol = Solution()
    nums1 = [1, -1, -3, -2, 3]
    k1 = 3
    x1 = 2
    res1 = sol.getSubarrayBeauty(nums1, k1, x1)
    print(f"Beauty 1: {res1}") # Expected: [-1, -2, -2]

    nums2 = [-1, -2, -3]
    k2 = 2
    x2 = 1
    res2 = sol.getSubarrayBeauty(nums2, k2, x2)
    print(f"Beauty 2: {res2}") # Expected: [-2, -3]
