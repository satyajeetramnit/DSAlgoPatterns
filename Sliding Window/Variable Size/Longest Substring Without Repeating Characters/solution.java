import java.util.HashSet;
import java.util.Set;

class Solution {
    public int lengthOfLongestSubstring(String s) {
        Set<Character> charSet = new HashSet<>();
        int left = 0;
        int maxLength = 0;
        
        for (int right = 0; right < s.length(); right++) {
            while (charSet.contains(s.charAt(right))) {
                charSet.remove(s.charAt(left));
                left++;
            }
            charSet.add(s.charAt(right));
            maxLength = Math.max(maxLength, right - left + 1);
        }
        return maxLength;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        String s1 = "abcabcbb";
        System.out.println("Length 1: " + sol.lengthOfLongestSubstring(s1)); // Expected: 3

        String s2 = "bbbbb";
        System.out.println("Length 2: " + sol.lengthOfLongestSubstring(s2)); // Expected: 1
        
        String s3 = "pwwkew";
        System.out.println("Length 3: " + sol.lengthOfLongestSubstring(s3)); // Expected: 3
    }
}
