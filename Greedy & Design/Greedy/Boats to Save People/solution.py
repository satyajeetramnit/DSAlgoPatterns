from typing import List

class Solution:
    def numRescueBoats(self, people: List[int], limit: int) -> int:
        people.sort()
        left, right = 0, len(people) - 1
        boats = 0
        
        while left <= right:
            if people[left] + people[right] <= limit:
                left += 1
            right -= 1
            boats += 1
            
        return boats

if __name__ == "__main__":
    sol = Solution()
    print(f"Test Case 1: {sol.numRescueBoats([1,2], 3)}") # Expect 1
    print(f"Test Case 2: {sol.numRescueBoats([3,2,2,1], 3)}") # Expect 3
    print(f"Test Case 3: {sol.numRescueBoats([3,5,3,4], 5)}") # Expect 4
