from typing import List

class Solution:
    def shipWithinDays(self, weights: List[int], days: int) -> int:
        def canShip(capacity):
            days_needed = 1
            current_load = 0
            for w in weights:
                if current_load + w > capacity:
                    days_needed += 1
                    current_load = 0
                current_load += w
            return days_needed <= days

        left, right = max(weights), sum(weights)
        
        while left <= right:
            mid = (left + right) // 2
            if canShip(mid):
                right = mid - 1
            else:
                left = mid + 1
        return left

if __name__ == "__main__":
    sol = Solution()
    weights1 = [1,2,3,4,5,6,7,8,9,10]
    days1 = 5
    print(f"Min Capacity 1: {sol.shipWithinDays(weights1, days1)}") # Expected: 15

    weights2 = [3,2,2,4,1,4]
    days2 = 3
    print(f"Min Capacity 2: {sol.shipWithinDays(weights2, days2)}") # Expected: 6
