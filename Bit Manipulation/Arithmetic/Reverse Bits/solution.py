class Solution:
    def reverseBits(self, n: int) -> int:
        res = 0
        for i in range(32):
            bit = (n >> i) & 1
            res = res | (bit << (31 - i))
        return res

if __name__ == "__main__":
    sol = Solution()
    
    n1 = 43261596
    print(f"Test Case 1: {sol.reverseBits(n1)}") # 964176192
    
    n2 = 4294967293
    print(f"Test Case 2: {sol.reverseBits(n2)}") # 3221225471
