import java.util.HashMap;
import java.util.Map;

public class Solution {
    public String longestUniqueSubstring(String s) {
        int l = 0, maxStart = 0, maxLen = 0;
        Map<Character, Integer> lastIndex = new HashMap<>();

        for (int r = 0; r < s.length(); r++) {
            char c = s.charAt(r);
            // If the character is within the current window, update the left pointer.
            if (lastIndex.containsKey(c) && lastIndex.get(c) >= l) {
                l = lastIndex.get(c) + 1;
            }
            lastIndex.put(c, r);

            // Update the maximum window if a longer one is found.
            if (r - l + 1 > maxLen) {
                maxLen = r - l + 1;
                maxStart = l;
            }
        }
        return s.substring(maxStart, maxStart + maxLen);
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        String s = "abcabcbb";
        System.out.println("Longest Unique Substring: " + sol.longestUniqueSubstring(s));
    }
}
