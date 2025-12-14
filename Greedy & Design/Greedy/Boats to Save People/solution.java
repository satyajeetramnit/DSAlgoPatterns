import java.util.Arrays;

class Solution {
    public int numRescueBoats(int[] people, int limit) {
        Arrays.sort(people);
        int left = 0, right = people.length - 1;
        int boats = 0;
        
        while (left <= right) {
            if (people[left] + people[right] <= limit) {
                left++;
            }
            right--;
            boats++;
        }
        return boats;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        System.out.println("Test Case 1: " + sol.numRescueBoats(new int[]{1,2}, 3)); // Expect 1
        System.out.println("Test Case 2: " + sol.numRescueBoats(new int[]{3,2,2,1}, 3)); // Expect 3
        System.out.println("Test Case 3: " + sol.numRescueBoats(new int[]{3,5,3,4}, 5)); // Expect 4
    }
}
