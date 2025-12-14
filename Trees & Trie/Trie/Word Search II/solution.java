import java.util.*;

class Solution {
    class TrieNode {
        TrieNode[] children = new TrieNode[26];
        String word;
    }
    
    public List<String> findWords(char[][] board, String[] words) {
        TrieNode root = new TrieNode();
        for (String w : words) {
            TrieNode curr = root;
            for (char c : w.toCharArray()) {
                int idx = c - 'a';
                if (curr.children[idx] == null) curr.children[idx] = new TrieNode();
                curr = curr.children[idx];
            }
            curr.word = w;
        }
        
        List<String> result = new ArrayList<>();
        int m = board.length, n = board[0].length;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (root.children[board[i][j] - 'a'] != null) {
                    dfs(board, i, j, root, result);
                }
            }
        }
        return result;
    }
    
    private void dfs(char[][] board, int i, int j, TrieNode parent, List<String> result) {
        char letter = board[i][j];
        TrieNode curr = parent.children[letter - 'a'];
        
        if (curr.word != null) {
            result.add(curr.word);
            curr.word = null; // Avoid duplicates
        }
        
        board[i][j] = '#'; // Mark
        
        int[][] dirs = {{0,1}, {0,-1}, {1,0}, {-1,0}};
        for (int[] d : dirs) {
            int r = i + d[0];
            int c = j + d[1];
            if (r >= 0 && r < board.length && c >= 0 && c < board[0].length && 
                board[r][c] != '#' && curr.children[board[r][c] - 'a'] != null) {
                dfs(board, r, c, curr, result);
            }
        }
        
        board[i][j] = letter; // Backtrack
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        char[][] board = {
            {'o','a','a','n'},
            {'e','t','a','e'},
            {'i','h','k','r'},
            {'i','f','l','v'}
        };
        String[] words = {"oath","pea","eat","rain"};
        List<String> result = sol.findWords(board, words);
        Collections.sort(result);
        System.out.println("Test Case 1: " + result); // Expect [eat, oath]
    }
}
