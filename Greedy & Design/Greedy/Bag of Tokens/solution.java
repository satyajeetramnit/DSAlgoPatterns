import java.util.Arrays;

class Solution {
    public int bagOfTokensScore(int[] tokens, int power) {
        Arrays.sort(tokens);
        int left = 0, right = tokens.length - 1;
        int score = 0, maxScore = 0;
        
        while (left <= right) {
            if (power >= tokens[left]) {
                power -= tokens[left];
                score++;
                left++;
                maxScore = Math.max(maxScore, score);
            } else if (score > 0) {
                if (left == right) break; // Don't sell last token
                
                power += tokens[right];
                score--;
                right--;
            } else {
                break;
            }
        }
        return maxScore;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        System.out.println("Test Case 1: " + sol.bagOfTokensScore(new int[]{100}, 50)); // Expect 0
        System.out.println("Test Case 2: " + sol.bagOfTokensScore(new int[]{100, 200}, 150)); // Expect 1
        System.out.println("Test Case 3: " + sol.bagOfTokensScore(new int[]{100, 200, 300, 400}, 200)); // Expect 2
    }
}
