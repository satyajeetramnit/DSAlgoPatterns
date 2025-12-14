from typing import List
from collections import deque

class Solution:
    def ladderLength(self, beginWord: str, endWord: str, wordList: List[str]) -> int:
        wordSet = set(wordList)
        if endWord not in wordSet:
            return 0
        
        q = deque([(beginWord, 1)])
        
        while q:
            word, length = q.popleft()
            
            if word == endWord:
                return length
            
            for i in range(len(word)):
                original_char = word[i]
                for c in "abcdefghijklmnopqrstuvwxyz":
                    if c == original_char:
                        continue
                        
                    new_word = word[:i] + c + word[i+1:]
                    
                    if new_word in wordSet:
                        wordSet.remove(new_word) # Mark visited
                        q.append((new_word, length + 1))
        return 0

if __name__ == "__main__":
    sol = Solution()
    
    beginWord = "hit"
    endWord = "cog"
    wordList1 = ["hot","dot","dog","lot","log","cog"]
    print(f"Word Ladder 1: {sol.ladderLength(beginWord, endWord, wordList1)}")

    wordList2 = ["hot","dot","dog","lot","log"]
    print(f"Word Ladder 2: {sol.ladderLength(beginWord, endWord, wordList2)}")
