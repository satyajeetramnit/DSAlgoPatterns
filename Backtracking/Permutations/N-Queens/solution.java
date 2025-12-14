import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class Solution {
    public List<List<String>> solveNQueens(int n) {
        List<List<String>> res = new ArrayList<>();
        char[][] board = new char[n][n];
        for (char[] row : board) Arrays.fill(row, '.');
        
        boolean[] cols = new boolean[n];
        boolean[] posDiag = new boolean[2 * n]; // r + c
        boolean[] negDiag = new boolean[2 * n]; // r - c + n
        
        backtrack(0, n, board, cols, posDiag, negDiag, res);
        return res;
    }
    
    private void backtrack(int row, int n, char[][] board, 
                           boolean[] cols, boolean[] posDiag, boolean[] negDiag, 
                           List<List<String>> res) {
        if (row == n) {
            List<String> copy = new ArrayList<>();
            for (char[] r : board) copy.add(new String(r));
            res.add(copy);
            return;
        }
        
        for (int col = 0; col < n; col++) {
            if (cols[col] || posDiag[row + col] || negDiag[row - col + n]) {
                continue;
            }
            
            cols[col] = true;
            posDiag[row + col] = true;
            negDiag[row - col + n] = true;
            board[row][col] = 'Q';
            
            backtrack(row + 1, n, board, cols, posDiag, negDiag, res);
            
            board[row][col] = '.';
            cols[col] = false;
            posDiag[row + col] = false;
            negDiag[row - col + n] = false;
        }
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int n1 = 4;
        System.out.println("Solutions for N=4: " + sol.solveNQueens(n1));
        
        int n2 = 1;
        System.out.println("Solutions for N=1: " + sol.solveNQueens(n2));
    }
}
