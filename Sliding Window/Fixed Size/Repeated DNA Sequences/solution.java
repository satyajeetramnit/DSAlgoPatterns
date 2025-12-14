import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

class Solution {
    public List<String> findRepeatedDnaSequences(String s) {
        Set<String> seen = new HashSet<>();
        Set<String> repeated = new HashSet<>();
        
        for (int i = 0; i <= s.length() - 10; i++) {
            String sub = s.substring(i, i + 10);
            if (seen.contains(sub)) {
                repeated.add(sub);
            } else {
                seen.add(sub);
            }
        }
        return new ArrayList<>(repeated);
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        String s1 = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT";
        List<String> res1 = sol.findRepeatedDnaSequences(s1);
        System.out.println("Repeated 1: " + res1); // Expected: [AAAAACCCCC, CCCCCAAAAA] (order varies)

        String s2 = "AAAAAAAAAAAAA";
        List<String> res2 = sol.findRepeatedDnaSequences(s2);
        System.out.println("Repeated 2: " + res2); // Expected: [AAAAAAAAAA]
    }
}
