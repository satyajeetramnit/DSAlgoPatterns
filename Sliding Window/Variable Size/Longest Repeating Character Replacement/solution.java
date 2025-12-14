class Solution {
    public int characterReplacement(String s, int k) {
        int[] count = new int[26];
        int left = 0;
        int maxFreq = 0;
        int maxLen = 0;
        
        for (int right = 0; right < s.length(); right++) {
            count[s.charAt(right) - 'A']++;
            maxFreq = Math.max(maxFreq, count[s.charAt(right) - 'A']);
            
            if ((right - left + 1) - maxFreq > k) {
                count[s.charAt(left) - 'A']--;
                left++;
            }
            
            maxLen = Math.max(maxLen, right - left + 1);
        }
        return maxLen;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        String s1 = "ABAB";
        int k1 = 2;
        System.out.println("Max Length 1: " + sol.characterReplacement(s1, k1)); // Expected: 4

        String s2 = "AABABBA";
        int k2 = 1;
        System.out.println("Max Length 2: " + sol.characterReplacement(s2, k2)); // Expected: 4
    }
}
