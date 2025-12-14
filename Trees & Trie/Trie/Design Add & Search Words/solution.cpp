#include <iostream>
#include <string>
#include <vector>

using namespace std;

class TrieNode {
public:
  TrieNode *children[26];
  bool isEnd;

  TrieNode() {
    isEnd = false;
    for (int i = 0; i < 26; i++)
      children[i] = nullptr;
  }
};

class WordDictionary {
  TrieNode *root;

public:
  WordDictionary() { root = new TrieNode(); }

  void addWord(string word) {
    TrieNode *curr = root;
    for (char c : word) {
      int idx = c - 'a';
      if (!curr->children[idx])
        curr->children[idx] = new TrieNode();
      curr = curr->children[idx];
    }
    curr->isEnd = true;
  }

  bool search(string word) { return searchHelper(word, 0, root); }

  bool searchHelper(string &word, int index, TrieNode *node) {
    if (index == word.length()) {
      return node->isEnd;
    }

    char c = word[index];
    if (c == '.') {
      for (int i = 0; i < 26; i++) {
        if (node->children[i] &&
            searchHelper(word, index + 1, node->children[i])) {
          return true;
        }
      }
      return false;
    } else {
      int idx = c - 'a';
      if (!node->children[idx])
        return false;
      return searchHelper(word, index + 1, node->children[idx]);
    }
  }
};

int main() {
  WordDictionary wordDictionary;
  wordDictionary.addWord("bad");
  wordDictionary.addWord("dad");
  wordDictionary.addWord("mad");
  bool r1 = wordDictionary.search("pad"); // false
  bool r2 = wordDictionary.search("bad"); // true
  bool r3 = wordDictionary.search(".ad"); // true
  bool r4 = wordDictionary.search("b.."); // true

  cout << "Test Case 1: " << boolalpha << r1 << " " << r2 << " " << r3 << " "
       << r4 << endl;
  // Expect false true true true
  return 0;
}
