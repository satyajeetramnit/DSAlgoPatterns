#include <iostream>
#include <vector>

using namespace std;

class TrieNode {
public:
  TrieNode *children[26];
  bool isEnd;

  TrieNode() {
    isEnd = false;
    for (int i = 0; i < 26; i++) {
      children[i] = nullptr;
    }
  }
};

class Trie {
  TrieNode *root;

public:
  Trie() { root = new TrieNode(); }

  void insert(string word) {
    TrieNode *curr = root;
    for (char c : word) {
      int idx = c - 'a';
      if (!curr->children[idx]) {
        curr->children[idx] = new TrieNode();
      }
      curr = curr->children[idx];
    }
    curr->isEnd = true;
  }

  bool search(string word) {
    TrieNode *curr = root;
    for (char c : word) {
      int idx = c - 'a';
      if (!curr->children[idx])
        return false;
      curr = curr->children[idx];
    }
    return curr->isEnd;
  }

  bool startsWith(string prefix) {
    TrieNode *curr = root;
    for (char c : prefix) {
      int idx = c - 'a';
      if (!curr->children[idx])
        return false;
      curr = curr->children[idx];
    }
    return true;
  }
};

int main() {
  Trie trie;
  trie.insert("apple");
  bool search1 = trie.search("apple");   // true
  bool search2 = trie.search("app");     // false
  bool starts1 = trie.startsWith("app"); // true
  trie.insert("app");
  bool search3 = trie.search("app"); // true

  cout << "Test Case 1: " << boolalpha << search1 << " " << search2 << " "
       << starts1 << " " << search3 << endl; // Expect true false true true
  return 0;
}
