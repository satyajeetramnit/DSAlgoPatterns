class Solution:
    def getSum(self, a: int, b: int) -> int:
        mask = 0xFFFFFFFF
        
        while b != 0:
            sum_val = (a ^ b) & mask
            carry = ((a & b) << 1) & mask
            
            a = sum_val
            b = carry
            
        if a > 0x7FFFFFFF:
            a = ~(a ^ mask)
            
        return a

if __name__ == "__main__":
    sol = Solution()
    print(f"Test Case 1 (1 + 2): {sol.getSum(1, 2)}") # 3
    print(f"Test Case 2 (-2 + 3): {sol.getSum(-2, 3)}") # 1
