class Solution:
    def isPrime(self, n: int) -> bool:
        if n <= 1: return False
        if n <= 3: return True
        if n % 2 == 0 or n % 3 == 0: return False
        i = 5
        while i * i <= n:
            if n % i == 0 or n % (i + 2) == 0:
                return False
            i += 6
        return True

    def countPrimes(self, n: int) -> int:
        if n <= 2: return 0
        is_prime = [True] * n
        is_prime[0] = is_prime[1] = False
        
        for p in range(2, int(n**0.5) + 1):
            if is_prime[p]:
                is_prime[p*p:n:p] = [False] * len(is_prime[p*p:n:p])
                
        return sum(is_prime)

if __name__ == "__main__":
    sol = Solution()
    print(f"Test Case 1 (10): {sol.countPrimes(10)}") # 4
    print(f"Test Case 2 (1): {sol.countPrimes(1)}") # 0
    print(f"Is 29 prime? {sol.isPrime(29)}") # True
