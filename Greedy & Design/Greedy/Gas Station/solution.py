from typing import List

class Solution:
    def canCompleteCircuit(self, gas: List[int], cost: List[int]) -> int:
        if sum(gas) < sum(cost):
            return -1
        
        current_tank = 0
        start_index = 0
        
        for i in range(len(gas)):
            current_tank += gas[i] - cost[i]
            
            if current_tank < 0:
                start_index = i + 1;
                current_tank = 0
                
        return start_index

if __name__ == "__main__":
    sol = Solution()
    print(f"Test Case 1: {sol.canCompleteCircuit([1,2,3,4,5], [3,4,5,1,2])}") # Expect 3
    print(f"Test Case 2: {sol.canCompleteCircuit([2,3,4], [3,4,3])}") # Expect -1
