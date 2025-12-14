from typing import List

# Mock interface
class MountainArray:
    def __init__(self, arr):
        self.arr = arr
    def get(self, index: int) -> int:
        return self.arr[index]
    def length(self) -> int:
        return len(self.arr)

class Solution:
    def findInMountainArray(self, target: int, mountain_arr: 'MountainArray') -> int:
        n = mountain_arr.length()
        
        # 1. Find Peak
        left, right = 0, n - 1
        while left < right:
            mid = (left + right) // 2
            if mountain_arr.get(mid) < mountain_arr.get(mid + 1):
                left = mid + 1
            else:
                right = mid
        peak = left
        
        # 2. Search Left
        left, right = 0, peak
        while left <= right:
            mid = (left + right) // 2
            val = mountain_arr.get(mid)
            if val == target:
                return mid
            elif val < target:
                left = mid + 1
            else:
                right = mid - 1
                
        # 3. Search Right
        left, right = peak + 1, n - 1
        while left <= right:
            mid = (left + right) // 2
            val = mountain_arr.get(mid)
            if val == target:
                return mid
            elif val > target: 
                left = mid + 1
            else:
                right = mid - 1
                
        return -1

if __name__ == "__main__":
    sol = Solution()
    arr1 = [1,2,3,4,5,3,1]
    ma1 = MountainArray(arr1)
    print(f"Index of 3: {sol.findInMountainArray(3, ma1)}") # Expected: 2

    arr2 = [0,1,2,4,2,1]
    ma2 = MountainArray(arr2)
    print(f"Index of 3: {sol.findInMountainArray(3, ma2)}") # Expected: -1
