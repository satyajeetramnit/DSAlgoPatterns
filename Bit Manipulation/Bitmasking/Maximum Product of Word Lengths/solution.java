class Solution {
    public int maxProduct(String[] words) {
        int n = words.length;
        int[] masks = new int[n];
        int[] lens = new int[n];
        
        for (int i = 0; i < n; i++) {
            lens[i] = words[i].length();
            for (char c : words[i].toCharArray()) {
                masks[i] |= (1 << (c - 'a'));
            }
        }
        
        int maxProd = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if ((masks[i] & masks[j]) == 0) {
                    maxProd = Math.max(maxProd, lens[i] * lens[j]);
                }
            }
        }
        
        return maxProd;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        String[] words1 = {"abcw","baz","foo","bar","xtfn","abcdef"};
        System.out.println("Test Case 1: " + sol.maxProduct(words1)); // 16
        
        String[] words2 = {"a","ab","abc","d","cd","bcd","abcd"};
        System.out.println("Test Case 2: " + sol.maxProduct(words2)); // 4
        
        String[] words3 = {"a","aa","aaa","aaaa"};
        System.out.println("Test Case 3: " + sol.maxProduct(words3)); // 0
    }
}
