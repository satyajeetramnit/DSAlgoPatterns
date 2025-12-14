from typing import List

class Solution:
    def findArray(self, pref: List[int]) -> List[int]:
        n = len(pref)
        arr = [0] * n
        arr[0] = pref[0]
        
        for i in range(1, n):
            arr[i] = pref[i] ^ pref[i-1]
            
        return arr

if __name__ == "__main__":
    sol = Solution()
    print(f"Test Case 1: {sol.findArray([5,2,0,3,1])}") # [5, 7, 2, 3, 2]
    print(f"Test Case 2: {sol.findArray([13])}") # [13]
