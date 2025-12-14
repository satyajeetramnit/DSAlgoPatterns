class Solution:
    def isPowerOfTwo(self, n: int) -> bool:
        if n <= 0:
            return False
        return (n & (n - 1)) == 0

if __name__ == "__main__":
    sol = Solution()
    print(f"Test Case 1 (1): {sol.isPowerOfTwo(1)}") # True
    print(f"Test Case 2 (16): {sol.isPowerOfTwo(16)}") # True
    print(f"Test Case 3 (3): {sol.isPowerOfTwo(3)}") # False
