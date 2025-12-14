from typing import List

class Solution:
    # Single Number I
    def singleNumber(self, nums: List[int]) -> int:
        res = 0
        for n in nums:
            res ^= n
        return res

    # Single Number II
    def singleNumberII(self, nums: List[int]) -> int:
        ones, twos = 0, 0
        for num in nums:
            ones = (ones ^ num) & ~twos
            twos = (twos ^ num) & ~ones
        return ones

    # Single Number III
    def singleNumberIII(self, nums: List[int]) -> List[int]:
        xor_all = 0
        for n in nums:
            xor_all ^= n
            
        diff = xor_all & -xor_all
        
        res = [0, 0]
        for n in nums:
            if n & diff:
                res[0] ^= n
            else:
                res[1] ^= n
        return res

if __name__ == "__main__":
    sol = Solution()
    print(f"Single Number I ([2,2,1]): {sol.singleNumber([2,2,1])}") # 1
    print(f"Single Number II ([2,2,3,2]): {sol.singleNumberII([2,2,3,2])}") # 3
    print(f"Single Number III ([1,2,1,3,2,5]): {sol.singleNumberIII([1,2,1,3,2,5])}") # [3, 5] order varies
