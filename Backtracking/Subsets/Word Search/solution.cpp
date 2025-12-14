#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  bool exist(vector<vector<char>> &board, string word) {
    int m = board.size();
    int n = board[0].size();

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (board[i][j] == word[0] && dfs(board, i, j, word, 0)) {
          return true;
        }
      }
    }
    return false;
  }

private:
  bool dfs(vector<vector<char>> &board, int i, int j, const string &word,
           int index) {
    if (index == word.length())
      return true;

    if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size() ||
        board[i][j] != word[index]) {
      return false;
    }

    char temp = board[i][j];
    board[i][j] = '#'; // Mark visited

    bool found = dfs(board, i + 1, j, word, index + 1) ||
                 dfs(board, i - 1, j, word, index + 1) ||
                 dfs(board, i, j + 1, word, index + 1) ||
                 dfs(board, i, j - 1, word, index + 1);

    board[i][j] = temp; // Backtrack
    return found;
  }
};

int main() {
  Solution sol;
  vector<vector<char>> board = {
      {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};

  cout << "Exist ABCCED: " << sol.exist(board, "ABCCED") << endl; // Expect 1
  cout << "Exist SEE: " << sol.exist(board, "SEE") << endl;       // Expect 1
  cout << "Exist ABCB: " << sol.exist(board, "ABCB") << endl;     // Expect 0

  return 0;
}
