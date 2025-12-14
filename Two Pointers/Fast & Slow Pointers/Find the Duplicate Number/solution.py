from typing import List

class Solution:
    def findDuplicate(self, nums: List[int]) -> int:
        slow, fast = 0, 0
        while True:
            slow = nums[slow]
            fast = nums[nums[fast]]
            if slow == fast:
                break
        
        slow = 0
        while slow != fast:
            slow = nums[slow]
            fast = nums[fast]
        return slow

if __name__ == "__main__":
    sol = Solution()
    print(f"Duplicate: {sol.findDuplicate([1, 3, 4, 2, 2])}")
