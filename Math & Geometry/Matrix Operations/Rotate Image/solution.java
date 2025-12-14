import java.util.Arrays;

class Solution {
    public void rotate(int[][] matrix) {
        int n = matrix.length;
        
        // Transpose
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                int temp = matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = temp;
            }
        }
        
        // Reverse rows
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n / 2; j++) {
                int temp = matrix[i][j];
                matrix[i][j] = matrix[i][n - 1 - j];
                matrix[i][n - 1 - j] = temp;
            }
        }
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[][] matrix = {{1,2,3},{4,5,6},{7,8,9}};
        sol.rotate(matrix);
        
        System.out.println("Test Case 1 Output:");
        for (int[] row : matrix) {
            System.out.println(Arrays.toString(row));
        }
        // Expect:
        // [7, 4, 1]
        // [8, 5, 2]
        // [9, 6, 3]
    }
}
