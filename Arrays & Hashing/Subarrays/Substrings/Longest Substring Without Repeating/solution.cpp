#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

string longestUniqueSubstring(const string &s) {
    unordered_map<char, int> lastIndex; // To store the last seen index of each character.
    int l = 0, maxStart = 0, maxLen = 0;

    for (int r = 0; r < s.size(); r++) {
        char currentChar = s[r];
        // If the character is seen and is within the current window, move left pointer.
        if (lastIndex.find(currentChar) != lastIndex.end() && lastIndex[currentChar] >= l) {
            l = lastIndex[currentChar] + 1;
        }
        // Update the last seen index of the current character.
        lastIndex[currentChar] = r;
        
        // Update maximum window if a longer substring is found.
        if (r - l + 1 > maxLen) {
            maxLen = r - l + 1;
            maxStart = l;
        }
    }
    
    return s.substr(maxStart, maxLen);
}

int main() {
    string s = "abcabcbb";
    cout << "Longest Unique Substring: " << longestUniqueSubstring(s) << endl;
    return 0;
}
