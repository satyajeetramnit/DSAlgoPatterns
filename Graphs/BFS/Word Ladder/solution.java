import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Arrays;
import java.util.Queue;
import java.util.Set;

class Solution {
    public int ladderLength(String beginWord, String endWord, List<String> wordList) {
        Set<String> wordSet = new HashSet<>(wordList);
        if (!wordSet.contains(endWord)) return 0;
        
        Queue<String> q = new LinkedList<>();
        q.offer(beginWord);
        int length = 1;
        
        while (!q.isEmpty()) {
            int size = q.size();
            while (size-- > 0) {
                String word = q.poll();
                if (word.equals(endWord)) return length;
                
                char[] chars = word.toCharArray();
                for (int i = 0; i < chars.length; i++) {
                    char original = chars[i];
                    for (char c = 'a'; c <= 'z'; c++) {
                        if (c == original) continue;
                        chars[i] = c;
                        String newWord = new String(chars);
                        
                        if (wordSet.contains(newWord)) {
                            q.offer(newWord);
                            wordSet.remove(newWord); // Mark visited
                        }
                    }
                    chars[i] = original; // Restore
                }
            }
            length++;
        }
        return 0;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        
        String beginWord = "hit";
        String endWord = "cog";
        List<String> list1 = Arrays.asList("hot","dot","dog","lot","log","cog");
        System.out.println("Word Ladder 1: " + sol.ladderLength(beginWord, endWord, list1));

        List<String> list2 = Arrays.asList("hot","dot","dog","lot","log");
        System.out.println("Word Ladder 2: " + sol.ladderLength(beginWord, endWord, list2));
    }
}
