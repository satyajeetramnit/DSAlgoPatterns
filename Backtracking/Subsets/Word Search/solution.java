class Solution {
    public boolean exist(char[][] board, String word) {
        int m = board.length;
        int n = board[0].length;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == word.charAt(0) && dfs(board, i, j, word, 0)) {
                    return true;
                }
            }
        }
        return false;
    }
    
    private boolean dfs(char[][] board, int i, int j, String word, int index) {
        if (index == word.length()) return true;
        
        if (i < 0 || i >= board.length || j < 0 || j >= board[0].length || board[i][j] != word.charAt(index)) {
            return false;
        }
        
        char temp = board[i][j];
        board[i][j] = '#'; // Mark visited
        
        boolean found = dfs(board, i + 1, j, word, index + 1) ||
                        dfs(board, i - 1, j, word, index + 1) ||
                        dfs(board, i, j + 1, word, index + 1) ||
                        dfs(board, i, j - 1, word, index + 1);
        
        board[i][j] = temp; // Backtrack
        return found;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        char[][] board = {
            {'A','B','C','E'},
            {'S','F','C','S'},
            {'A','D','E','E'}
        };
        
        System.out.println("Exist ABCCED: " + sol.exist(board, "ABCCED"));
        System.out.println("Exist SEE: " + sol.exist(board, "SEE"));
        System.out.println("Exist ABCB: " + sol.exist(board, "ABCB"));
    }
}
