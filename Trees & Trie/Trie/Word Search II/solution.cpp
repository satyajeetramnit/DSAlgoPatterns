#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class TrieNode {
public:
  TrieNode *children[26];
  string *word; // Store pointer to word at leaf

  TrieNode() {
    word = nullptr;
    for (int i = 0; i < 26; i++)
      children[i] = nullptr;
  }
};

class Solution {
  TrieNode *root;
  vector<string> result;
  int m, n;

public:
  vector<string> findWords(vector<vector<char>> &board, vector<string> &words) {
    root = new TrieNode();
    for (string &w : words) {
      insert(w);
    }

    m = board.size();
    n = board[0].size();

    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (root->children[board[i][j] - 'a']) {
          dfs(board, i, j, root);
        }
      }
    }
    return result;
  }

  void insert(string &word) {
    TrieNode *curr = root;
    for (char c : word) {
      int idx = c - 'a';
      if (!curr->children[idx])
        curr->children[idx] = new TrieNode();
      curr = curr->children[idx];
    }
    curr->word = &word; // Store address of the string in the original vector
    // Note: In local test, string literal/stack string might move.
    // Better to copy for robust impl or ensure words vector persists.
    // Here `&word` refers to element inside `words` vector, which is stable.
  }

  void dfs(vector<vector<char>> &board, int i, int j, TrieNode *parent) {
    char letter = board[i][j];
    TrieNode *curr = parent->children[letter - 'a'];

    if (curr->word) {
      result.push_back(*curr->word);
      curr->word = nullptr; // Avoid duplicates
    }

    board[i][j] = '#'; // Mark visited

    int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    for (auto &d : dirs) {
      int r = i + d[0], c = j + d[1];
      if (r >= 0 && r < m && c >= 0 && c < n && board[r][c] != '#' &&
          curr->children[board[r][c] - 'a']) {
        dfs(board, r, c, curr);
      }
    }

    board[i][j] = letter; // Backtrack
  }
};

void printVector(vector<string> v) {
  sort(v.begin(), v.end());
  cout << "[";
  for (int i = 0; i < v.size(); i++) {
    cout << "\"" << v[i] << "\"" << (i < v.size() - 1 ? "," : "");
  }
  cout << "]" << endl;
}

int main() {
  Solution sol;
  vector<vector<char>> board = {{'o', 'a', 'a', 'n'},
                                {'e', 't', 'a', 'e'},
                                {'i', 'h', 'k', 'r'},
                                {'i', 'f', 'l', 'v'}};
  vector<string> words = {"oath", "pea", "eat", "rain"};
  vector<string> result = sol.findWords(board, words);
  cout << "Test Case 1: ";
  printVector(result); // Expect ["eat", "oath"]
  return 0;
}
