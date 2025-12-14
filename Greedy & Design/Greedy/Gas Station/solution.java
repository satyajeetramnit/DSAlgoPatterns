class Solution {
    public int canCompleteCircuit(int[] gas, int[] cost) {
        int totalGas = 0;
        int totalCost = 0;
        for(int g : gas) totalGas += g;
        for(int c : cost) totalCost += c;
        
        if (totalGas < totalCost) return -1;
        
        int currentTank = 0;
        int startIndex = 0;
        
        for (int i = 0; i < gas.length; i++) {
            currentTank += gas[i] - cost[i];
            if (currentTank < 0) {
                startIndex = i + 1;
                currentTank = 0;
            }
        }
        return startIndex;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[] gas1 = {1,2,3,4,5};
        int[] cost1 = {3,4,5,1,2};
        System.out.println("Test Case 1: " + sol.canCompleteCircuit(gas1, cost1)); // Expect 3

        int[] gas2 = {2,3,4};
        int[] cost2 = {3,4,3};
        System.out.println("Test Case 2: " + sol.canCompleteCircuit(gas2, cost2)); // Expect -1
    }
}
