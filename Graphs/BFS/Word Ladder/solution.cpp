#include <iostream>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
  int ladderLength(string beginWord, string endWord, vector<string> &wordList) {
    unordered_set<string> wordSet(wordList.begin(), wordList.end());
    if (wordSet.find(endWord) == wordSet.end())
      return 0;

    queue<pair<string, int>> q;
    q.push({beginWord, 1});

    while (!q.empty()) {
      auto [word, len] = q.front();
      q.pop();

      if (word == endWord)
        return len;

      for (int i = 0; i < word.length(); ++i) {
        char original = word[i];
        for (char c = 'a'; c <= 'z'; ++c) {
          if (c == original)
            continue;
          word[i] = c;
          if (wordSet.count(word)) {
            q.push({word, len + 1});
            wordSet.erase(word); // Mark visited
          }
        }
        word[i] = original; // Restore
      }
    }
    return 0;
  }
};

int main() {
  Solution sol;
  string beginWord = "hit";
  string endWord = "cog";
  vector<string> wordList1 = {"hot", "dot", "dog", "lot", "log", "cog"};
  cout << "Word Ladder 1: " << sol.ladderLength(beginWord, endWord, wordList1)
       << endl; // Expect 5

  vector<string> wordList2 = {"hot", "dot", "dog", "lot", "log"};
  cout << "Word Ladder 2: " << sol.ladderLength(beginWord, endWord, wordList2)
       << endl; // Expect 0

  return 0;
}
